// qtermwidget - test executable
//
// Baulk - Copyright (C) 2008  Jacob Alexander
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

#define BAULK

#include <QApplication>

#include "qtermwidget.h"

int main( int argc, char *argv[] ) {
	// Typical Qt GUI application start
	QApplication *app = new QApplication( argc, argv );
	QTermWidget *term = new QTermWidget;
	term->show();

	QObject::connect( term, SIGNAL( finished() ), app, SLOT( quit() ) );

	// Event-Loop	
	int reTurn = app->exec();

	// Post-Quit Events
	if ( term != 0 )
		delete term;
	if ( app != 0 )
		delete app;

	return reTurn;
}

