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
#include <QTest>

#include <client.h>
#include <server.h>

#include "baulkterm.h"

/// Baulk Declaration for use in handler.h
BaulkTerm *baulk;

#include <handler.h>
#include <compositing.h>

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

	// Daemon
	InformationClient *client;

	// Qt GUI Application start with compositing information
	QApplication *app = new QApplication( display, argc, argv, (Qt::HANDLE)visual, (Qt::HANDLE)colormap );

	// Start BaulkTerm
	baulk = new BaulkTerm( 0, true );
	if ( baulk->processCommandArgs() ) {
		if ( baulk->useDaemon() ) {
			QString serverListenName = baulk->listenName();

			// Daemon - Quit if only starting a client
			InformationServer *serv = new InformationServer( serverListenName, baulk );
			QObject::connect( serv, SIGNAL( destroyed() ), app, SLOT( quit() ));

			// Client
			client = new InformationClient( serverListenName, false, baulk );

			// Connection for starting each terminal
			QObject::connect( serv, SIGNAL( startNewHostInstance() ), baulk, SLOT( newTerminal() ) );
			QObject::connect( client, SIGNAL( idChanged() ), client, SLOT( requestStartNewHostInstance() ) );

			client->requestId();
		}

		if ( !baulk->useDaemon() ) {
			baulk->startShellProgram();
			baulk->show();
		}
	}
	else {
		delete baulk;
		delete app;
		return 0;
	}

	// Event-Loop	
	int reTurn = app->exec();

	// Post-Quit Events
	delete client;
	delete baulk;
	delete app;

	return reTurn;
}

