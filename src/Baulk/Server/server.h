// Baulk - Information Server - Server
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

#ifndef __INFORMATIONSERVER_H
#define __INFORMATIONSERVER_H

#include <stdlib.h>

#include <QList>
#include <QLocalServer>
#include <QLocalSocket>
#include <QObject>
#include <QVector>

#include "client.h"
#include "packet.h"

/**
 * @author Jacob Alexander (HaaTa)
 *
 * Responsible for Passing information between GUI instances of Baulk.
 *
 * The server takes data thrown at it and passes it to the designated client.
 */
class InformationServer : public QObject {
	Q_OBJECT

public:
	InformationServer( QString listen, QObject *parent = 0 );
	~InformationServer();

	QLocalServer *serverOpen() const { return server; }

	bool terminate();

private:
	bool allowTerminate;

	int connectedClients;

	Packet *incomingPacket;

	QLocalServer *server;
	QLocalSocket *clientConnection;

	QString listenSocket;

	QVector<QLocalSocket*> clientList;
	QList<int> emptyClientListEntries;

	QString errorName() const { return tr("InformationServer"); }

	void clientRedirect();
	void outgoingData( QString data );
	void requestId();
	void serverRequest();

private slots:
	void connection();
	void incomingData();

signals:
	void alreadyRunning();
};

#endif

