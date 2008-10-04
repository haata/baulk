// Main - Baulk
//
// Baulk - Copyright (C) 2008  Jacob Alexander
//
//  File:	main.cpp
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//  	First point of entry, which passes to baulk.h. Captures
//  	all debug output for this instance of Baulk.
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

#include <iostream>

#include "baulk.h"

// Handles all messages sent by the application
void handler( QtMsgType type, const char *msg ) {
	QString log = "";
	switch ( type ) {
	case QtDebugMsg:
		log = QObject::tr("<Debug> %1").arg( msg );
		std::cerr << log.toUtf8().data() << std::endl;
		break;
	case QtWarningMsg:
		log = QObject::tr("<Warning> %1").arg( msg );
		std::cerr << log.toUtf8().data() << std::endl;
		break;
	case QtCriticalMsg:
		log = QObject::tr("<Critical> %1").arg( msg );
		std::cerr << log.toUtf8().data() << std::endl;
		break;
	case QtFatalMsg:
		log = QObject::tr("<Fatal> %1").arg( msg );
		std::cerr << log.toUtf8().data() << std::endl;
		break;
	}
}

int main( int argc, char *argv[] ) {
	qInstallMsgHandler( handler ); // Message Handler
	QApplication *app = new QApplication( argc, argv );

	Baulk baulk;
	baulk.show();

	// Event-Loop	
	int reTurn = app->exec();

	// Post-Quit Events
	

	return reTurn;
}

