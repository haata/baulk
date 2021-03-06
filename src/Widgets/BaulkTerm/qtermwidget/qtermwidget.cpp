//  Copyright (C) 2008 e_k (e_k@users.sourceforge.net)
//  Forked for Baulk - Copyright (C) 2008-2009 - Jacob Alexander <haata at users.sf.net>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  any later version, including version 3 of the License.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "qtermwidget.h"

#include "Session.h"
#include "TerminalDisplay.h"

using namespace Konsole;

void *createTermWidget(int startnow, void *parent)
{ 
    return (void*) new QTermWidget(startnow, (QWidget*)parent); 
}

struct TermWidgetImpl
{
    TermWidgetImpl(QWidget* parent = 0);

    TerminalDisplay *m_terminalDisplay;
    Session *m_session;
    
    Session* createSession();
    TerminalDisplay* createTerminalDisplay(Session *session, QWidget* parent);
};

TermWidgetImpl::TermWidgetImpl(QWidget* parent)
{
    this->m_session = createSession();
    this->m_terminalDisplay = createTerminalDisplay(this->m_session, parent);
}


Session *TermWidgetImpl::createSession()
{
    Session *session = new Session();

    session->setTitle(Session::NameRole, "QTermWidget");
    session->setProgram("/bin/bash");
    QStringList args("");
    session->setArguments(args);
    session->setAutoClose(true);
		    
    session->setCodec(QTextCodec::codecForName("UTF-8"));
			
    session->setFlowControlEnabled(true);
    session->setHistoryType(HistoryTypeBuffer(1000));
    
    session->setDarkBackground(true);
	    
    session->setKeyBindings("");	    
    return session;
}

TerminalDisplay *TermWidgetImpl::createTerminalDisplay(Session *session, QWidget* parent)
{
//    TerminalDisplay* display = new TerminalDisplay(this);
    TerminalDisplay* display = new TerminalDisplay(parent);
    
    display->setBellMode(TerminalDisplay::NotifyBell);
    display->setTerminalSizeHint(true);
    display->setTripleClickMode(TerminalDisplay::SelectWholeLine);
    display->setTerminalSizeStartup(true);

    display->setRandomSeed(session->sessionId() * 31);
    
    return display;
}


QTermWidget::QTermWidget(int startnow, QWidget *parent)
:QWidget(parent)
{
    m_impl = new TermWidgetImpl(this);
    
    init();

    if (startnow && m_impl->m_session) {
	m_impl->m_session->run();
    }
    
    this->setFocus( Qt::OtherFocusReason );
    m_impl->m_terminalDisplay->resize(this->size());
    
    this->setFocusProxy(m_impl->m_terminalDisplay);
}

void QTermWidget::startShellProgram()
{
    if ( m_impl->m_session->isRunning() )
	return;
	
    m_impl->m_session->run();
}

void QTermWidget::init()
{    
    m_impl->m_terminalDisplay->setSize(80, 40);
    
    QFont font = QApplication::font(); 
    font.setFamily("Monospace");
    font.setPointSize(10);
    font.setStyleHint(QFont::TypeWriter);
    setTerminalFont(font);
    setScrollBarPosition(NoScrollBar);    
        
    m_impl->m_session->addView(m_impl->m_terminalDisplay);
    
    connect(m_impl->m_session, SIGNAL(finished()), SLOT(sessionFinished()));
    connect( m_impl->m_terminalDisplay, SIGNAL( mouseSignal( int, int, int, int ) ), SIGNAL( mouseSignal( int, int, int, int ) ) );
    connect( m_impl->m_terminalDisplay, SIGNAL( rightClickAction() ), SIGNAL( rightClickAction() ) );
    connect( m_impl->m_session, SIGNAL( titleChanged() ), SLOT( titleUpdated() ) );
}


QTermWidget::~QTermWidget()
{
    emit destroyed();
}


void QTermWidget::titleUpdated() {
	emit terminalTitleUpdate( terminalTitle() );
}

QString QTermWidget::terminalTitle() const {
	return m_impl->m_session->userTitle();
}

void QTermWidget::setTerminalFont(QFont font)
{
    if (!m_impl->m_terminalDisplay)
	return;
    m_impl->m_terminalDisplay->setVTFont(font);
}

void QTermWidget::setShellProgram(QString &progname)
{
    if (!m_impl->m_session)
	return;
    m_impl->m_session->setProgram(progname);	
}

void QTermWidget::setArgs(QStringList &args)
{
    if (!m_impl->m_session)
	return;
    m_impl->m_session->setArguments(args);	
}

void QTermWidget::setTextCodec(QTextCodec *codec)
{
    if (!m_impl->m_session)
	return;
    m_impl->m_session->setCodec(codec);	
}

void QTermWidget::setColorScheme(int scheme)
{
    switch(scheme) {
	case COLOR_SCHEME_WHITE_ON_BLACK:
		m_impl->m_terminalDisplay->setColorTable(whiteonblack_color_table);
		break;		
	case COLOR_SCHEME_GREEN_ON_BLACK:
		m_impl->m_terminalDisplay->setColorTable(greenonblack_color_table);
		break;
	case COLOR_SCHEME_BLACK_ON_LIGHT_YELLOW:
		m_impl->m_terminalDisplay->setColorTable(blackonlightyellow_color_table);
		break;
	default: //do nothing
	    break;
    };
}

void QTermWidget::setColor( int colorNumber, QColor color, bool transparency, bool bold ) 
{
	m_impl->m_terminalDisplay->setColorTableEntry( colorNumber, color, transparency, bold );
}

void QTermWidget::setOpacity( qreal opacity ) 
{
	m_impl->m_terminalDisplay->setOpacity( opacity );
}

void QTermWidget::updateImage()
{
	m_impl->m_terminalDisplay->updateImage();
}

void QTermWidget::setSize(int h, int v)
{
    if (!m_impl->m_terminalDisplay)
	return;
    m_impl->m_terminalDisplay->setSize(h, v);
}

void QTermWidget::setHistoryType( QString type, int lines )
{
	if ( type == "HistoryTypeNone" )
		m_impl->m_session->setHistoryType( HistoryTypeNone() );
	if ( type == "HistoryTypeBlockArray" )
		m_impl->m_session->setHistoryType( HistoryTypeBlockArray( lines ) );
	if ( type == "HistoryTypeFile" )
		m_impl->m_session->setHistoryType( HistoryTypeFile() );
	if ( type == "HistoryTypeBuffer" )
		m_impl->m_session->setHistoryType(HistoryTypeBuffer( lines ));
}

void QTermWidget::setScrollBarPosition(ScrollBarPosition pos)
{
    if (!m_impl->m_terminalDisplay)
	return;
    m_impl->m_terminalDisplay->setScrollBarPosition((TerminalDisplay::ScrollBarPosition)pos);
}

void QTermWidget::sendText(QString &text)
{
    m_impl->m_session->sendText(text); 
}

void QTermWidget::resizeEvent(QResizeEvent*)
{
//qDebug("global window resizing...with %d %d", this->size().width(), this->size().height());
    m_impl->m_terminalDisplay->resize(this->size());
}


void QTermWidget::sessionFinished()
{
    emit finished();
}


void QTermWidget::copyClipboard()
{
    m_impl->m_terminalDisplay->copyClipboard();
}

void QTermWidget::pasteClipboard()
{
    m_impl->m_terminalDisplay->pasteClipboard();
}

void QTermWidget::setFlowControlEnabled(bool enabled)
{
    m_impl->m_session->setFlowControlEnabled(enabled);
}

bool QTermWidget::flowControlEnabled(void)
{
    return m_impl->m_session->flowControlEnabled();
}

void QTermWidget::setFlowControlWarningEnabled(bool enabled)
{
    if(flowControlEnabled()) {
	// Do not show warning label if flow control is disabled
	m_impl->m_terminalDisplay->setFlowControlWarningEnabled(enabled);
    }
}

void QTermWidget::setEnvironment(const QStringList& environment)
{
    m_impl->m_session->setEnvironment(environment);
}

