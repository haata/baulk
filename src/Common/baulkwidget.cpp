// Baulk - Common - Baulk Widget
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	baulkwidget.cpp
//  Author(s):	Jacob Alexander (HaaTa)
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
	setProperty( "msgLogs", QVariant( msgLogs ) );
	emit msgLogsUpdated( msgLogs );
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

// Reimplemented QWidget Functions ****************************************************************
void BaulkWidget::resizeEvent( QResizeEvent *event ) {
}

