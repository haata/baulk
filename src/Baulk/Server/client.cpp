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
	socket->abort();
	socket->connectToServer( serverName );
}

void InformationClient::firstServerContact() {

	QDataStream in( socket );
	in.setVersion( QDataStream::Qt_4_4 );

	if ( socket->bytesAvailable() < (int)sizeof(quint16) ) {
		qDebug("NoByte");
		return;
	}

	if ( in.atEnd() ) {
		qDebug("END!!");
		return;
	}

	QString data;
	in >> data;

	qDebug( data.toUtf8() );
}

