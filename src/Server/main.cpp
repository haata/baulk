// Main - BaulkServ
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

#include <QCoreApplication>

#include <handler.h>

#include "server.h"

/**
 * @author Jacob Alexander (HaaTa)
 *
 * Baulk Server Daemon
 *
 * Executable for instanciating the Daemon. 
 * Uses the message handler to enable Message Output formatting.
 */
int main( int argc, char *argv[] ) {
	// Message Handler
	qInstallMsgHandler( handler );

	// Qt Command Line Argument Handling
	QCoreApplication *app = new QCoreApplication( argc, argv );

	// Use default listen socket if none is specified via the command line
	QString listenSocket = "BaulkServ";
	for ( int c = 1; c < argc; ++c ) {
		listenSocket = argv[c];
	}

	// Daemon Quit Event Connection
	InformationServer *serv = new InformationServer( listenSocket );
	QObject::connect( serv, SIGNAL( destroyed() ), app, SLOT( quit() ));

	// Event-Loop	
	int reTurn = app->exec();

	// Post-Quit Events
	delete serv;
	delete app;

	return reTurn;
}

