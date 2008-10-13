// Baulk - Information Server - Baulk Packet Encoder/Decoder
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	packet.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	Encodes/Decodes BaulkPackets for use with the Baulk Information
//	Server.
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

#ifndef __PACKET_H
#define __PACKET_H

#include <QObject>
#include <QStringList>

class Packet : public QObject {
	Q_OBJECT

public:
	// Decode Packet Constructor
	Packet( QString packet, QObject *parent = 0 );
	// Encode Packet Constructor
	// 	- Note: Each String of data MUST be accompanied with a dataFlag string
	Packet( QString destinationId, QString senderId, QStringList dataFlags, QStringList data, QObject *parent = 0 );

private:

};

#endif

