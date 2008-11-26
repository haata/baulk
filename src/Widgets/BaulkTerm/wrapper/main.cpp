// BaulkTerm - Standalone Binary
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

#include <QApplication>

#include "baulkterm.h"

/// Baulk Declaration for use in handler.h
BaulkTerm *baulk;

#include <handler.h>
#include <compositing.h>

void commandLineArgs( QStringList arguments ) {
	qDebug( arguments[0].toUtf8() );
	qDebug( arguments[1].toUtf8() );
	qDebug( arguments[2].toUtf8() );
}

/**
 * @author Jacob Alexander (HaaTa)
 *
 * First point of entry, which passes to baulk.h. 
 * Captures all debug output for this instance of Baulk.
 */
int main( int argc, char *argv[] ) {
	// Message Handler
	qInstallMsgHandler( handler );

	// Compositing Information
	Display* display = 0;
	Visual* visual = 0;
	Colormap colormap = 0;
	getDisplayInformation( display, visual, colormap );

	// Qt GUI Application start with compositing information
	QApplication *app = new QApplication( display, argc, argv, (Qt::HANDLE)visual, (Qt::HANDLE)colormap );
	commandLineArgs( app->arguments() );
	baulk = new BaulkTerm;
	baulk->show();

	// Event-Loop	
	int reTurn = app->exec();

	// Post-Quit Events
	delete baulk;
	delete app;

	return reTurn;
}

