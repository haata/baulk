// Baulk - Baulk Terminal - Terminal for Baulk using qtermwidget
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

#include "wrapper_baulkterm.h"

// Symbol List ************************************************************************************
QStringList symbolList() {
	return QStringList()
		<< "baulkterm_configWidget"
		<< "baulkterm_mainWidget"
		<< "baulkterm_widgetName";
}

// Configuration Widget ***************************************************************************
BaulkWidget *baulkterm_configWidget( QWidget *parent ) {
	return new BaulkWidget( parent );
}

// Name *******************************************************************************************
QString baulkterm_widgetName() {
	return QObject::tr("BaulkTerm");
}

// Main *******************************************************************************************
BaulkWidget *baulkterm_mainWidget( QWidget *parent ) {
	qDebug("Loading BaulkTerm");

	term = new BaulkTerm( 1, true );
	BaulkWidget *wrapper = new BaulkWidget( term, parent );

	QObject::connect( term, SIGNAL( finished() ), wrapper, SLOT( close() ) );

	return wrapper;
}

