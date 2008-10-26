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
	allowTerminate = true;
	// Reserve First Socket and already running test
	QLocalSocket *tmp = new QLocalSocket( this );
	clientList.append( tmp );
	tmp->connectToServer( listen );

	switch ( tmp->error() ) { 
	// Server Not Running
	case QLocalSocket::ServerNotFoundError:
		listenSocket = listen;
		server = new QLocalServer( this );
		if ( !server->listen( listenSocket ) ) 
			qCritical( tr("%1\n\tCould not open listen socket\n\t%1").arg( errorName() ).arg( listenSocket ).toUtf8() );
		connect( server, SIGNAL( newConnection() ), this, SLOT( connection() ) );
		break;
	// Server Already Running Case
	default:
		terminate();
		break;
	}

	allowTerminate = false;
	connectedClients = 0;
}

InformationServer::~InformationServer() {
	qDebug("BaulkServ - Closing");
}

void InformationServer::clientRedirect() {
	qDebug( QString("%1\n\tClient Request (Server Redirect)").arg( errorName() ).toUtf8() );

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

	if ( data == "" ) {
		qDebug( QString("%1\n\tBlank Packet!").arg( errorName() ).toUtf8() );
		return;
	}

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
	qDebug( QString("%1\n\tInvalid Packet!\n\t\t%2").arg( errorName() ).arg( data ).toUtf8() );
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
	int newId = 0;
	if ( emptyClientListEntries.count() > 0 ) {
		newId = emptyClientListEntries.first();
		emptyClientListEntries.removeFirst();
	}
	else 
		newId = clientList.count();

	clientList.append( clientConnection );

	QString destination = Packet::infoToId( 
		Packet::idToInfo( incomingPacket->senderId() ).screenId, 
		newId );

	Packet answerPacket(	destination,
				incomingPacket->destinationId(),
				QStringList() << "NewId",
				QStringList() << QString::number( newId ) );

	outgoingData( answerPacket.packet() );

	allowTerminate = true;
	++connectedClients;
}

void InformationServer::serverRequest() {
	qDebug( QString("%1\n\tServer Request").arg( errorName() ).toUtf8() );
	
	QStringList flags = incomingPacket->dataFlags();
	QStringList data = incomingPacket->data();

	for ( int c = 0; c < flags.count(); ++c ) {
		if ( flags[c] == "RequestId" ) {
			if ( data[c] == "True" )
				requestId();
		}
		if ( flags[c] == "Ping" ) {
			if ( data[c] == "True" ) {
				Packet answerPacket(	incomingPacket->senderId(),
							incomingPacket->destinationId(),
							QStringList() << "PingReply",
							QStringList() << "True");
				outgoingData( answerPacket.packet() );
			}
		}
		if ( flags[c] == "RemoveId" ) {
			if ( data[c] == "True" ) {
				int id = Packet::idToInfo( incomingPacket->senderId() ).windowId;
				emptyClientListEntries.append( id );

				if ( emptyClientListEntries.count() >= clientList.count() )
					emptyClientListEntries.removeOne( clientList.count() );

				qDebug( QString("%1\n\tId Removed\n\t\t%2").arg( errorName() ).arg( id ).toUtf8() );

				--connectedClients;
				if ( connectedClients < 1 )
					terminate();
			}
		}
	}
}

bool InformationServer::terminate() {
	// Only Allow Close if the Server has been used
	if ( !allowTerminate ) 
		return false;

	deleteLater();
	return true;
}

