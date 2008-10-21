// Baulk - Control - DLL Wrapper
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	wrapper_control.h
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

#include "wrapper_control.h"

// Symbol List
QStringList symbolList() {
	return QStringList()
		<< "control_mainWidget";
}

// Main Widget
BaulkWidget *control_mainWidget( QWidget *parent ) {
	BaulkWidget *mainWidget = new BaulkWidget( parent );

	QVBoxLayout *test2 = new QVBoxLayout;	
	mainWidget->setLayout( test2 );
	QPushButton *test = new QPushButton( "TEST", parent );
	test2->addWidget( test );
	return mainWidget;
}
