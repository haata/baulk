// Baulk - WebBaulk - DLL Wrapper
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//   <haata at users.sf.net>
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

#include "wrapper_webbaulk.h"

// Symbol List ************************************************************************************
QStringList symbolList() {
	return QStringList()
		<< "webbaulk_configWidget"
		<< "webbaulk_mainWidget"
		<< "webbaulk_widgetName";
}

// Configuration Widget ***************************************************************************
BaulkWidget *webbaulk_configWidget( QWidget *parent ) {
	return new BaulkWidget( parent );
}

// Name *******************************************************************************************
QString webbaulk_widgetName() {
	return QObject::tr("WebBaulk");
}

// Main *******************************************************************************************
BaulkWidget *webbaulk_mainWidget( QWidget *parent ) {
	qDebug("Loading WebBaulk");

	browser = new WebBaulk( parent );

	return browser;
}

