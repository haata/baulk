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

#ifndef _Q_TERM_WIDGET
#define _Q_TERM_WIDGET

#include <QtGui>

struct TermWidgetImpl;

enum COLOR_SCHEME {     COLOR_SCHEME_WHITE_ON_BLACK	= 1,
		        COLOR_SCHEME_GREEN_ON_BLACK,
		        COLOR_SCHEME_BLACK_ON_LIGHT_YELLOW };

class QTermWidget : public QWidget
{
    Q_OBJECT
public:
    
    enum ScrollBarPosition
    {
        /*! Do not show the scroll bar. */
        NoScrollBar=0,
        /*! Show the scroll bar on the left side of the display. */
        ScrollBarLeft=1,
        /*! Show the scroll bar on the right side of the display. */
        ScrollBarRight=2
    };

    //! Terminal Title
    QString terminalTitle() const;

    //! Creation of widget
    QTermWidget(int startnow = 1, //start shell programm immediatelly
		QWidget *parent = 0);
    ~QTermWidget();

    //! start shell program if it was not started in constructor
    void startShellProgram();
    
    //look-n-feel, if you don`t like defaults

    //! environment
    void setEnvironment(const QStringList& environment);

    //! Shell program, default is /bin/bash
    void setShellProgram(QString &progname);
    
    //! Shell program args, default is none
    void setArgs(QStringList &args);
    
    //! Text codec, default is UTF-8
    void setTextCodec(QTextCodec *codec);

    //! Color scheme, default is white on black
    void setColorScheme(int scheme);
    
    //! set size
    void setSize(int h, int v);
    
    //! History Type/Size for scrolling 
    //! Types:
    //!  - HistoryTypeNone       - No History (Default)
    //!  - HistoryTypeBlockArray - (Uses lines arg)
    //!  - HistoryTypeFile       - Allows for unlimited history, slowest
    //!  - HistoryTypeBuffer     - Limited length buffer (uses line arg)
    void setHistoryType( QString type = "HistoryTypeNone", int lines = 0 );

    //! Presence of scrollbar
    void setScrollBarPosition(ScrollBarPosition);
    
    //! Send some text to terminal
    void sendText(QString &text);

    //! Sets whether flow control is enabled
    void setFlowControlEnabled(bool enabled);

    //! Returns whether flow control is enabled
    bool flowControlEnabled(void);

    /*!
     * Sets whether the flow control warning box should be shown
     * when the flow control stop key (Ctrl+S) is pressed.
     */
    void setFlowControlWarningEnabled(bool enabled);

    //! Individual Colour Control
    //!  See ColorTables.h for numbers
    void setColor( int colorNumber, QColor color, bool transparency, bool bold );

    //! Real Transparency
    //! Opacity Setting - Window Manager must support Compositing
    void setOpacity( qreal opacity );

signals:
    //! Terminal Closed
    void finished();

    //! Title Updated
    void terminalTitleUpdate( QString title );

    //! Mouse Click
    void mouseSignal( int button, int column, int line, int eventType );
    void rightClickAction();

public slots:
    //! Paste clipboard content to terminal
    void copyClipboard();
    
    //! Copies selection to clipboard
    void pasteClipboard();
        
    //! Updates Display Image, useful for forcing terminal display updates
    void updateImage();

    //! Terminal font
    //! Default is application font with family Monospace, size 10
    void setTerminalFont(QFont font); 
    
protected: 
    virtual void resizeEvent(QResizeEvent *);
    
protected slots:
    void sessionFinished();        
    
private:
    void init();    
    TermWidgetImpl *m_impl;

private slots:
	void titleUpdated();
};


//Maybe useful, maybe not

#ifdef __cplusplus
extern "C"
#endif
void *createTermWidget(int startnow, void *parent); 

#endif

