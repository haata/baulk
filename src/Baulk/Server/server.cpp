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
		qCritical( tr("InformationServer\n|Could not open listen socket\n||%1").arg( listenSocket ).toUtf8() );

	connect( server, SIGNAL( newConnection() ), this, SLOT( sendBackLinkInfo() ) );
}

void InformationServer::sendBackLinkInfo() {
	QByteArray block;
	QDataStream out( &block, QIODevice::WriteOnly );
	out.setVersion( QDataStream::Qt_4_4 );
	out << (quint16)0;
	out << QString("TEST");
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));
	
	QLocalSocket *clientConnection = server->nextPendingConnection();
	connect( clientConnection, SIGNAL( disconnected() ), clientConnection, SLOT( deleteLater() ) );

	clientConnection->write( block );
	clientConnection->flush();
	clientConnection->disconnectFromServer();
}

