// Baulk - Information Server - Client
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	client.cpp
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

#include "client.h"

InformationClient::InformationClient( QString call, QObject *parent ) : QObject( parent ) {
	serverName = call;
	socket = new QLocalSocket( this );

	connect( socket, SIGNAL( readyRead() ), this, SLOT( firstServerContact() ) );
}

void InformationClient::connectToServer() {	
	qDebug("READ!");
}

void InformationClient::firstServerContact() {
	QDataStream in( socket );
	in.setVersion( QDataStream::Qt_4_4 );

	QString data;
	in >> data;

	qDebug( data.toUtf8() );
}

void InformationClient::requestId() {
	socket->abort();
	socket->connectToServer( serverName );

	QByteArray block;
	QDataStream out( &block, QIODevice::WriteOnly );
	out.setVersion( QDataStream::Qt_4_4 );

	Packet requestPacket( 	Packet::infoToId( 0, 0 ), 
				Packet::infoToId( 0, 0 ), 
				QStringList() << "RequestId", 
				QStringList() << "True" );

	out << requestPacket.packet();

	socket->write( block );
	socket->flush();
}

