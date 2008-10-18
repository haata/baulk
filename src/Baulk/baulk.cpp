// Baulk
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	baulk.cpp
//  Author(s):	Jacob Alexander (HaaTa)
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

#include "client.h" // TODO - REMOVEME

// Constructor
Baulk::Baulk( QWidget *parent ) : QMainWindow( parent ) {
	QString serverListenName = "BaulkServ"; // TODO Put in config
	// Check if Server is already running
	if ( !InformationServer::serverExists( serverListenName ) ) { // TODO - Disable if flagged in config
		/*
		using namespace boost::interprocess;
		shared_memory_object::remove("BaulkMem");
		managed_shared_memory segment( create_only, "BaulkMem", 655360 );
		//infoServer = segment.construct<InformationServer>
		       ("BaulkInfoServer")
		       ( serverListenName );
		int *aaa = segment.construct<int> ("BaulkInt") (5);
		//shared_memory_object::remove("BaulkMem");
		qDebug( "%d", *aaa );
		*/
	}
	else
		qDebug( tr("Baulk\n\t|Information Server is already running\n\t||%1").arg( serverListenName ).toUtf8() );

	// Window Settings
	setWindowTitle( tr("Baulk - STATIC TITLE - %1").arg( serverListenName ) );

	InformationClient *client = new InformationClient( serverListenName, this );
	client->requestId();

	// Setup Controller Instance
	/*
	LibraryLoader *library = new LibraryLoader( this );
	library->loadLibrary( "BaulkControl" ); // TODO Add Version Control
	controller = ( (QWidget*(*)( QWidget* )) library->lrResolve("mainWidget") )( this );
	setCentralWidget( controller );	
	*/
	/*
	{
		using namespace boost::interprocess;
		managed_shared_memory segment( open_only, "BaulkMem" );
		int *te = segment.find<int>("BaulkInt").first;
		qDebug( "%d", *te );
		shared_memory_object::remove("BaulkMem");
	}
	*/
}

// Window Close Event
void Baulk::closeEvent( QCloseEvent *event ) {
	//event->ignore();
	
	// TODO - Send Event to Controller for quit/save message
	// 		Use controller infoClient inorder to determine whether or not to kill the server
	//infoServer->terminate();
		
	qDebug("Closing");
	event->accept();
}

