// Baulk - Information Server - Server
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	server.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	Primarily for passing data between instances of Baulk.
//	The server takes data thrown at it and passes it to
//	the designated client.
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

#ifndef __INFORMATIONSERVER_H
#define __INFORMATIONSERVER_H

#include <stdlib.h>

#include <QLocalServer>
#include <QLocalSocket>
#include <QObject>

#include "packet.h"

class InformationServer : public QObject {
	Q_OBJECT

public:
	InformationServer( QString listen, QObject *parent = 0 );
	~InformationServer();

	// Tests if the Server already exists
	static bool serverExists( QString listen );

	bool terminate();

private:
	QLocalServer *server;

	QString listenSocket;

private slots:
	void sendBackLinkInfo();

};

#endif

