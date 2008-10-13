// Baulk - Information Server - Baulk Packet Encoder/Decoder
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	packet.cpp
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

#include "packet.h"

// Constructors
Packet::Packet( QString packet, QObject *parent ) : QObject( parent ) {
	// TODO - Sanity Check on Packet
	packetS = packet;

	redecode = true;
	reencode = false;
}

Packet::Packet( QString destinationId, QString senderId, QStringList dataFlags, QStringList data, QObject *parent ) : QObject( parent ) {
	// TODO - Sanity Check on Packet Pieces
	destinationIdS = destinationId;
	senderIdS = senderId;
	dataFlagsS = dataFlags;
	dataS = data;

	redecode = false;
	reencode = true;
}

// Public

// Private
bool Packet::dataFlagsSanityStore( QStringList dataFlags ) {
}

bool Packet::dataSanityStore( QStringList data ) {
}

void Packet::debugOutput() {
}

void Packet::decode() {
	if ( !redecode )
		return;
	
	QStringList tmp = packetS.split("|");
	QList<bool> success;

	// Decypher TO and FROM Ids
	success << destinationIdSanityStore( tmp[0].remove("TO:") );
	success << senderIdSanityStore( tmp[1].remove("FROM:") );

	// If Data and Data Flags are contained in the packet
	if ( tmp.count() > 2 ) {
		QStringList data;
		QStringList flags;
		QStringList tmp2;

		for ( int c = 2; c < tmp.count(); ++c ) {
			tmp2 = tmp[c].split(":");
			flags << tmp2[0];
			data << tmp2[1];
		}

		success << dataFlagsSanityStore( flags );
		success << dataSanityStore( data );
	}

	// If a single sanity fails, output debug info
	for ( int c = 0; c < success.count(); ++c )
		if ( !success[c] )
			debugOutput();

	redecode = false;
}

bool Packet::destinationIdSanityStore( QString destinationId ) {
}

void Packet::encode() {
	if ( !reencode )
		return;

	QString ids = QString("TO:%1|FROM:%2").arg( destinationIdS ).arg( senderIdS );

	if ( dataFlagsS.count() != dataS.count() ) {
		qWarning( tr("InformationPacket\n\t|There are not equal number(s) of Data Flags and Data").toUtf8() );
		ids = "INVALID";
	}

	// Add data and data flags to the packet, if they exist 
	if ( dataS.count() > 0 ) {

		// Generate data + dataflags portion of the packet
		QString dataC = "";
		for ( int c = 0; c < dataS.count(); ++c )
			dataC += QString("|%1:%2").arg( dataFlagsS[c] ).arg( dataS[c] );

		ids += dataC;
	}

	packetS = ids;

	reencode = false;
}

bool Packet::senderIdSanityStore( QString senderId ) {
}

