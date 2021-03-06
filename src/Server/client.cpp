// Baulk - Information Server - Client
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

#include "client.h"

// Constructor ************************************************************************************
InformationClient::InformationClient( QString call, bool informOnClose, QObject *parent ) : QObject( parent ) {
	currentId = 0; // Default Id;
	serverName = call;
	socket = new QLocalSocket( this );

	informDaemonOnClose = informOnClose;

	connect( socket, SIGNAL( readyRead() ), this, SLOT( incomingData() ) );
}

// Destructor *************************************************************************************
InformationClient::~InformationClient() {
	// Remove Client From Server List
	if ( informDaemonOnClose ) {
		Packet removePacket(	Packet::infoToId( 0, 0 ),
					Packet::infoToId( 0, currentId ),
					QStringList() << "RemoveId",
					QStringList() << "True");
		outgoingData( removePacket.packet() );
#ifdef Q_OS_WIN32
		// Since Windows cuts corners, I have to force it to keep the 
		//  client open until the very end
		qCritical("Client Closing");
#endif
	}
}

void InformationClient::clientRequest() {
	QStringList flags = incomingPacket->dataFlags();
	QStringList data = incomingPacket->data();

	for ( int c = 0; c < flags.count(); ++c ) {
		if ( flags[c] == "NewId" ) {
			int newIdnum = data[c].toInt();
			if ( newIdnum != 0 ) // toInt defaults to 0 on failure, and 0 will never be an assigned Id 
				newId( newIdnum );
			else 
				qCritical( QString("%1 || Failure to get ID").arg( errorName() ).toUtf8() );
		}
	}
}

void InformationClient::connectToServer() {	
	qDebug("READ!");
}

// All Incoming Data goes through here ************************************************************
void InformationClient::incomingData() {
	QDataStream in( socket );
	in.setVersion( QDataStream::Qt_4_4 );

	QString data;
	in >> data;
	incomingPacket = new Packet( data, this );

	// Only Accept Packets Assigning Id's initially
	if ( currentId == 0 ) {
		// Only accept Packets from Server
		if ( Packet::idToInfo( incomingPacket->senderId() ).windowId == 0 ) {
			clientRequest();
			return;
		}
	}
	else {
	}

	// Invalid Packet
	qDebug( QString("%1\n\tInvalid Packet!\n\t\t%2").arg( errorName() ).arg( data ).toUtf8() );
}

void InformationClient::newId( int newIdnum ) {
	currentId = newIdnum;

	// Allows for the parent program to determine when an ID has been assigned
	emit idChanged();

	qDebug( QString("%1\n\tNew Id || %2").arg( errorName() ).arg( currentId ).toUtf8() );
}

// All Outgoing Data goes through here ************************************************************
void InformationClient::outgoingData( QString data ) {
	//if ( !socket->isValid() ) {
		socket->abort();
		socket->connectToServer( serverName );
	//}

	QByteArray block;
	QDataStream out( &block, QIODevice::WriteOnly );
	out.setVersion( QDataStream::Qt_4_4 );

	out << data;

	socket->write( block );
	socket->flush();
}

void InformationClient::requestId() {
	Packet requestPacket( 	Packet::infoToId( 0, 0 ), 
				Packet::infoToId( 0, 0 ), 
				QStringList() << "RequestId", 
				QStringList() << "True" );

	outgoingData( requestPacket.packet() );
}

// Request startNewHostInstance signal on server **************************************************
void InformationClient::requestStartNewHostInstance() {
	Packet requestPacket( 	Packet::infoToId( 0, 0 ), 
				Packet::infoToId( 0, id() ), 
				QStringList() << "RequestStartNewHostInstance", 
				QStringList() << "True" );

	outgoingData( requestPacket.packet() );
}

