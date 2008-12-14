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

#ifndef __INFORMATIONCLIENT_H
#define __INFORMATIONCLIENT_H

#include <stdlib.h>

#include <QLocalServer>
#include <QLocalSocket>
#include <QObject>

#include "packet.h"

/**
 * @author Jacob Alexander (HaaTa)
 *
 * Responsible for Communicating with the InformationServer
 *
 * Provides an interface for sending/recieving information to/from
 *  different instances of Baulk.
 */
class InformationClient : public QObject {
	Q_OBJECT

public:
	InformationClient( QString call, bool informDaemonOnClose = true, QObject *parent = 0 );
	~InformationClient();

	void connectToServer();
	void requestId();

	int id() const { return currentId; }

public slots:
	void incomingData();
	void requestStartNewHostInstance();

private:
	bool informDaemonOnClose;

	int currentId;

	Packet *incomingPacket;

	QLocalSocket *socket;
	QString serverName;

	QString errorName() const { return tr("InformationClient"); }

	void clientRequest();
	void newId( int newId );
	void outgoingData( QString data );

signals:
	void idChanged();
};

#endif

