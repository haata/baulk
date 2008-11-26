// Baulk - Common - Baulk Widget
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  Baulk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  any later version, including version 3 of the License.
//
//  Baulk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "baulkwidget.h"

// Constructors ***********************************************************************************
BaulkWidget::BaulkWidget( QWidget *parent ) : QWidget( parent ) {
	widgetSetup();
}

BaulkWidget::BaulkWidget( QWidget *wrapWidget, QWidget *parent ) : QWidget( parent ) {
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins( 0,0,0,0 );
	layout->addWidget( wrapWidget );
	setLayout( layout );

	setFocusProxy( wrapWidget );

	widgetSetup();
}

// Defaults ***************************************************************************************
void BaulkWidget::widgetSetup() {
	setMinimumSize( 250, 250 );
	setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
}

// Properties *************************************************************************************
QStringList BaulkWidget::msgLogs() const {
	return property("msgLogs").toStringList();
}
void BaulkWidget::setMsgLogs( QStringList msgLogs ) {
	QStringList tmp = property("msgLogs").toStringList() + msgLogs;

	setProperty( "msgLogs", QVariant( tmp ) );
	emit msgLogsUpdated( tmp );
}

QString BaulkWidget::serverListenName() const { 
	return property("serverListenName").toString(); 
}
void BaulkWidget::setServerListenName( QString listenName ) { 
	setProperty( "serverListenName", QVariant( listenName) ); 
	emit serverListenNameSet( listenName ); 
}

QString BaulkWidget::windowTitleName() const { 
	return property("windowTitleName").toString(); 
}
void BaulkWidget::setWindowTitleName( QString titleName ) {
	setProperty( "windowTitleName", QVariant( titleName ) );
	emit windowTitleNameSet( titleName ); 
}

// Command Line Arguments *************************************************************************
bool BaulkWidget::processCommandArgs() {
	bool runApp = true;
	QStringList args = qApp->arguments();

	if ( args.contains( tr("--h" ) ) || args.contains( tr("--help") ) ) {
		qWarning("Currently there are no command line options");
		// TODO Help Options
		return false;
	}
	if ( args.contains( tr("--v") ) || args.contains( tr("--version") ) ) {
		return false;
	}

	return runApp;
}

// Reimplemented QWidget Functions ****************************************************************
void BaulkWidget::resizeEvent( QResizeEvent *event ) {
	resize( event->size() );
}

