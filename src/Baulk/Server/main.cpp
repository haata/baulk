// Main - BaulkServ
//
// Baulk - Copyright (C) 2008  Jacob Alexander
//
//  File:	main.cpp
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//  	Baulk Server daemon.
//  	Processes all the information sent from the Baulk Clients.
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

#include <handler.h>

#include "server.h"

int main( int argc, char *argv[] ) {
	qInstallMsgHandler( handler ); // Message Handler
	QApplication *app = new QApplication( argc, argv );

	QString listenSocket = "BaulkServ";
	InformationServer serv( listenSocket );

	// Event-Loop	
	int reTurn = app->exec();

	// Post-Quit Events
	

	return reTurn;
}

