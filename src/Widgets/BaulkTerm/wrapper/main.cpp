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
	baulk = new BaulkTerm( 0 );
	if ( baulk->processCommandArgs() ) {
		baulk->startShellProgram();
		baulk->setStyleSheet("QWidget {"
				"background: black;"
				"}");
		baulk->show();

		// Attempt to start Daemon
		QString serverListenName = "BaulkTermServ"; // TODO Put in config

		// Start Daemon - Automatically closes if Daemon is already running
		QString program;
		if ( QFile::exists("./baulkServ") )
			program = QString("./baulkServ %1").arg( serverListenName );
		else
			program = QString("baulkServ %1").arg( serverListenName );

		QProcess::startDetached( program );
		QTest::qSleep(100); // Leave Time for the Daemon to start

		// Connect to Daemon
		client = new InformationClient( serverListenName );
		client->requestId();
	}
	else {
		delete baulk;
		delete app;
		return 0;
	}
	//baulk->newTerminal()->show();

	// Event-Loop	
	int reTurn = app->exec();

	// Post-Quit Events
	delete client;
	delete baulk;
	delete app;

	return reTurn;
}

