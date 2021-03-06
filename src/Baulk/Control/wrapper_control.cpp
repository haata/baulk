// Baulk - Control - DLL Wrapper
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

#include "wrapper_control.h"

// Symbol List ************************************************************************************
QStringList symbolList() {
	return QStringList()
		<< "allowQuit"
		<< "control_mainWidget"
		<< "control_mainWidget";
}

// Main Widget ************************************************************************************
BaulkWidget *control_mainWidget( QWidget *parent ) {
	control = new BaulkControl( parent );

	return control;
}

// Widget Name ************************************************************************************
QString control_widgetName() {
	return QObject::tr("Baulk Control");
}

// Quit Event *************************************************************************************
bool allowQuit() {
	if ( QMessageBox::warning( control, "Quit?",
				"Are you sure you want to quit?", 
				QMessageBox::Yes | QMessageBox::No, 
				QMessageBox::No ) 
			== QMessageBox::Yes )
		return true;
	return false;
}

