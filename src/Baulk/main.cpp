// Main - Baulk
//
// Baulk - Copyright (C) 2008-2009  Jacob Alexander
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

#define BAULK

#include <QApplication>

#include "baulk.h"

//! Baulk Declaration for use in handler.h
Baulk *baulk;

#include <handler.h>
#include <compositing.h> // Used in X11 only

/*!
 * First point of entry, which passes to baulk.h. 
 * Captures all debug output for this instance of Baulk.
 */
int main( int argc, char *argv[] ) {
	// Message Handler
	//qInstallMsgHandler( handler );  // TODO option for turning this on/off and both console and log

#ifdef Q_WS_X11
	// Compositing Information
	Display* display = 0;
	Visual* visual = 0;
	Colormap colormap = 0;
	getDisplayInformation( display, visual, colormap );

	// Qt GUI Application start with compositing information
	QApplication *app = new QApplication( display, argc, argv, (Qt::HANDLE)visual, (Qt::HANDLE)colormap );
#else
	// Typical Qt GUI application start
	QApplication *app = new QApplication( argc, argv );
#endif

	baulk = new Baulk;
	//baulk->processCommandArgs();
	//if ( !baulk->processCommandArgs() );
	//	delete baulk;
	//	delete app;
	//	return 0;
	//}

	// Event-Loop	
	int reTurn = app->exec();

	// Post-Quit Events
	//delete baulk;
	//delete app;

	return reTurn;
}

