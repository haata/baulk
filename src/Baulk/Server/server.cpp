// Baulk - Information Server - Server
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	server.cpp
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

#include "server.h"

InformationServer::InformationServer( QString listen, QObject *parent ) : QObject( parent ) {
	listenSocket = listen;
	server = new QLocalServer( this );
	if ( !server->listen( listenSocket ) ) 
		qCritical( tr("InformationServer\n\t|Could not open listen socket\n\t||%1").arg( listenSocket ).toUtf8() );

	connect( server, SIGNAL( newConnection() ), this, SLOT( sendBackLinkInfo() ) );
}

void InformationServer::sendBackLinkInfo() {
	QByteArray block;
	QDataStream out( &block, QIODevice::WriteOnly );
	out.setVersion( QDataStream::Qt_4_4 );
	out << QString("TEST");
	
	QLocalSocket *clientConnection = server->nextPendingConnection();
	connect( clientConnection, SIGNAL( disconnected() ), clientConnection, SLOT( deleteLater() ) );

	clientConnection->write( block );
	clientConnection->flush();
	clientConnection->disconnectFromServer();
}

bool InformationServer::serverExists( QString listen ) {
	QLocalServer testServer;
	bool tmp = testServer.listen( listen );
	testServer.close();
	return !tmp; // tmp returns whether a Server can be started, therefore should return the opposite
}

bool InformationServer::terminate() {
	// TODO - Check Connections list before closing
	server->close();

	return true;
}
