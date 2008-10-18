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
	// Reserve First Socket
	QLocalSocket *tmp;
	clientList.append( tmp );

	listenSocket = listen;
	server = new QLocalServer( this );
	if ( !server->listen( listenSocket ) ) 
		qCritical( tr("InformationServer\n\t|Could not open listen socket\n\t||%1").arg( listenSocket ).toUtf8() );


	connect( server, SIGNAL( newConnection() ), this, SLOT( connection() ) );
}

InformationServer::~InformationServer() {
	terminate();
}

void InformationServer::clientRedirect() {
	qDebug("InformationServer\n\t|Client Request (Server Redirect)");

	QStringList flags = incomingPacket->dataFlags();
	QStringList data = incomingPacket->data();

	for ( int c = 0; c < flags.count(); ++c ) {
	/*	if ( flags[c] == "RequestId" ) {
			if ( data[c] == "True" )
				requestId();
		}*/
	}
}

void InformationServer::connection() {
	clientConnection = server->nextPendingConnection();
	connect( clientConnection, SIGNAL( readyRead() ), this, SLOT( incomingData() ) );
	connect( clientConnection, SIGNAL( disconnected() ), clientConnection, SLOT( deleteLater() ) );
}

// All Incoming Data goes through here
void InformationServer::incomingData() {
	QDataStream in( clientConnection );
	in.setVersion( QDataStream::Qt_4_4 );
	QString data;

	in >> data;

	incomingPacket = new Packet( data, this );

	// Server Request
	if ( Packet::idToInfo( incomingPacket->destinationId() ).windowId == 0 ) {
		serverRequest();
		return;
	}

	// Client Request
	if ( Packet::idToInfo( incomingPacket->destinationId() ).windowId > 0 ) {
		clientRedirect();
		return;
	}

	// Invalid Packet
	qDebug( QString("InformationServer\n\t|Invalid Packet!\n\t\t%1").arg( data ).toUtf8() );
}

void InformationServer::outgoingData( QString data ) {
	QByteArray block;
	QDataStream out( &block, QIODevice::WriteOnly );
	out.setVersion( QDataStream::Qt_4_4 );

	out << data;

	clientConnection->write( block );
	clientConnection->flush();
}

void InformationServer::requestId() {
	int newId = clientList.count();
	clientList.append( clientConnection );

	QString destination = Packet::infoToId( 
		Packet::idToInfo( incomingPacket->senderId() ).screenId, 
		newId );

	Packet answerPacket(	destination,
				incomingPacket->destinationId(),
				QStringList() << "NewId",
				QStringList() << QString::number( newId ) );

	outgoingData( answerPacket.packet() );
}

bool InformationServer::serverExists( QString listen ) {
	//QLocalServer testServer;
	//bool tmp = testServer.listen( listen );
	//testServer.close();
	//return !tmp; // tmp returns whether a Server can be started, therefore should return the opposite
	return false; // tmp returns whether a Server can be started, therefore should return the opposite
}

void InformationServer::serverRequest() {
	qDebug("InformationServer\n\t|Server Request");
	
	QStringList flags = incomingPacket->dataFlags();
	QStringList data = incomingPacket->data();

	for ( int c = 0; c < flags.count(); ++c ) {
		if ( flags[c] == "RequestId" ) {
			if ( data[c] == "True" )
				requestId();
		}
	}
}

bool InformationServer::terminate() {
	// TODO - Check Connections list before closing
	server->close();

	return true;
}

