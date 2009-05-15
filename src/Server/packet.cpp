// Baulk - Information Server - Baulk Packet Encoder/Decoder
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//   <haata at users.sf.net>
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
	setPacket( packet );
}

Packet::Packet( QString destinationId, QString senderId, QStringList dataFlags, QStringList data, QObject *parent ) : QObject( parent ) {
	setEncode( destinationId, senderId, dataFlags, data );
}

// Public
Packet::PacketIdInformation Packet::idToInfo( QString id ) {
	PacketIdInformation info;
	QRegExp conversion = QRegExp("Screen\\{([0-9]*)\\}Inc\\{([0-9]*)\\}");

	QString tmp = id;
	info.screenId = tmp.replace( conversion, "\\1" ).toInt();

	tmp = id;
	info.windowId = tmp.replace( conversion, "\\2" ).toInt();

	return info;
}

QString Packet::infoToId( int screenId, int windowId ) {
	QString id = QString("Screen{%1}Inc{%2}").arg( screenId ).arg( windowId );

	return id;
}

// Private
bool Packet::dataFlagsSanityStore( QStringList dataFlags ) {
	dataFlagsS = dataFlags;

	for ( int c = 0; c < dataFlags.count(); ++c )
		if ( dataFlags[c].contains( dataCheck() ) )
			return false;

	return true;
}

bool Packet::dataSanityStore( QStringList data ) {
	dataS = data;

	for ( int c = 0; c < data.count(); ++c )
		if ( data[c].contains( dataCheck() ) )
			return false;

	return true;
}

void Packet::debugOutput() {
	QString info = tr("Packet\n\t|Incorrect Packet Information\n\t||TO:\n\t\t%1\n\t||FROM:\n\t\t%2").arg( destinationIdS ).arg( senderIdS );

	for ( int c = 0; c < dataFlagsS.count(); ++c )
		info += tr("\n\t||DataFlag:\n\t\t%1\n\t||Data:\n\t\t%2").arg( dataFlagsS[c] ).arg( dataS[c] );

	qDebug( info.toUtf8() );
}

void Packet::decode() {
	QStringList tmp = packetS.split("|");
	QList<bool> success;

	// Decypher TO and FROM Ids
	success << destinationIdSanityStore( tmp[0].remove("TO:") )
		<< senderIdSanityStore( tmp[1].remove("FROM:") );

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

		success << dataFlagsSanityStore( flags )
			<< dataSanityStore( data );
	}

	// If a single sanity fails, output debug info
	for ( int c = 0; c < success.count(); ++c )
		if ( !success[c] )
			debugOutput();
}

bool Packet::destinationIdSanityStore( QString destinationId ) {
	destinationIdS = destinationId;

	if ( !destinationId.contains( idCheck() ) )
		return false;

	return true;
}

void Packet::encode() {
	QString ids = QString("TO:%1|FROM:%2").arg( destinationIdS ).arg( senderIdS );

	if ( dataFlagsS.count() != dataS.count() ) {
		qWarning( tr("%1\n\tThere are not equal number(s) of Data Flags and Data").arg( errorName() ).toUtf8() );
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
}

bool Packet::senderIdSanityStore( QString senderId ) {
	senderIdS = senderId;

	if ( !senderId.contains( idCheck() ) )
		return false;

	return true;
}

