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

BaulkWidget::BaulkWidget( QWidget *parent ) : QWidget( parent ) {
}

// PROPERTIES *************************************************************************************
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

