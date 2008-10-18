// Baulk - Information Server - Client
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	client.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	Primarily for passing data between instances of Baulk.
//	The client accepts the information from the server.
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

#ifndef __INFORMATIONCLIENT_H
#define __INFORMATIONCLIENT_H

#include <stdlib.h>

#include <QLocalServer>
#include <QLocalSocket>
#include <QObject>

#include "packet.h"

class InformationClient : public QObject {
	Q_OBJECT

public:
	InformationClient( QString call, QObject *parent = 0 );

	void connectToServer();
	void requestId();

public slots:
	void incomingData();

private:
	int currentId;

	Packet *incomingPacket;

	QLocalSocket *socket;
	QString serverName;

	void clientRequest();
	void newId( int newId );
	void outgoingData( QString data );
};

#endif

