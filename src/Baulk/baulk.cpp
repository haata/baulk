// Baulk
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

#include "baulk.h"

#include "X11/xcb_WindowScanner.h"

// Constructor ************************************************************************************
Baulk::Baulk( QWidget *parent ) : QObject( (QObject*) parent ) { // TODO Parent

	///////////// Daemon 
	QString serverListenName = "BaulkServ"; // TODO Put in config

	// Start Daemon - Automatically closes if Daemon is already running
	QString program;
	if ( QFile::exists("./baulkServ") )
		program = QString("./baulkServ %1").arg( serverListenName );
	else
		program = QString("baulkServ %1").arg( serverListenName );

	QProcess::startDetached( program );
	QTest::qSleep(100); // Leave Time for the Daemon to start

	///////////// Screen Info
	
	qDebug( "Number of Screens %d" , qApp->desktop()->numScreens() );
	// TODO Change to settings or dynamic (-1 is default screen)
	QRect currentScreenSize = qApp->desktop()->availableGeometry( -1 );


	// Setup Controller Instance
	library = new LibraryLoader( "BaulkControl" );
	controller = library->loadBaulkWidget( "mainWidget" );
	controller->setServerListenName( serverListenName );
	//setCentralWidget( controller );

	// Window Settings
	//setWindowTitle( tr("Baulk - %1").arg( serverListenName ) );
	connect( controller, SIGNAL( windowTitleNameSet( QString ) ), this, SLOT( setWindowTitleName( QString ) ) );

	//////////////// Tiling Basic
	
	//controller->setGeometry( currentScreenSize );
	qDebug( "%d", currentScreenSize.width() );
	QRect tmp = currentScreenSize;
	tmp.setRight( tmp.width() / 2 );
	//controller->move( currentScreenSize.topLeft() );
	controller->setGeometry( tmp );
	controller->show();

	QWidget *tets = new QWidget;
	qDebug( "%d", currentScreenSize.width() );
	QRect tmp2 = currentScreenSize;
	tmp2.setLeft( tmp2.width() / 2 );
	tets->setGeometry( tmp2 );
	tets->show();

	XCBWindowScanner scanner( this );
}

// Window Close Event *****************************************************************************
void Baulk::closeEvent( QCloseEvent *event ) {
	//event->ignore();
	
	// TODO - Send Event to Controller for quit/save message
	// 		Use controller infoClient inorder to determine whether or not to kill the server
	/*	
	bool (*allowQuit)();
	allowQuit = (bool(*)()) library->lrResolve("allowQuit");

	if ( allowQuit() ) {
		qDebug("Closing");
		event->accept();
	}
	else event->ignore();
	*/
}

// Log Update *************************************************************************************
bool Baulk::updateMsgLogs( QStringList msgLogs ) {
	if ( controller != 0 ) {
		controller->setMsgLogs( msgLogs );
		return true;
	}
	
	return false;
}

// Command Line Arguments *************************************************************************
bool Baulk::processCommandArgs() {
	return controller->processCommandArgs();
}

// SLOTS ******************************************************************************************
void Baulk::setWindowTitleName( QString windowTitle ) {
	//setWindowTitle( windowTitle );
}

