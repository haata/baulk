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
//
//  Packet Details:
//
//  TO:<destination ID>|FROM:<source ID>|<data flag>:<data>
//
//  or
//
//  TO:<destination ID>|FROM:<source ID>|<data flag>:<data>|<data flag2>
//  	:<data>|<data flag3>:<data>| etc...
//
//
//  TO/FROM Id Details:
//
//  Screen{<screen number>}Inc{<increment>}
//  	ie. Screen{0}Inc{2} for the second window on Screen Zero
//
//	If the first window is deleted ( Screen{0}Inc{1} ), then the next window 
//		created will be Screen{0}Inc{1}
//
//	The Increment is not defined by the screen. It is the global increment (so 
//		for the above ie. there will be no Screen{1}Inc{2})
//
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

#include <QList>
#include <QObject>
#include <QRegExp>
#include <QStringList>

class Packet : public QObject {
	Q_OBJECT

public:
	// Decode Packet Constructor
	Packet( QString packet, QObject *parent = 0 );
	// Encode Packet Constructor
	// 	- Note: Each String of data MUST be accompanied with a dataFlag string
	Packet( QString destinationId, QString senderId, QStringList dataFlags = QStringList(), QStringList data = QStringList(), QObject *parent = 0 );


	// Id Conversion
	struct PacketIdInformation {
		int screenId;
		int windowId;
	};

	static PacketIdInformation idToInfo( QString id );
	static QString infoToId( int screenId, int windowId );


	// Get/Sets
	QString packet() const 		{ return packetS; }
	void setPacket( QString packet ) { 
		packetS = packet;
		decode(); 
	}

	QStringList data() const 	{ return dataS; }
	void setData( QStringList data ) { 
		if ( !dataSanityStore( data ) ) 
			debugOutput(); 			
		encode(); 
	}

	QStringList dataFlags() const 	{ return dataFlagsS; }
	void setDataFlags( QStringList dataFlags ) { 
		if ( !dataFlagsSanityStore( dataFlags ) )
			debugOutput(); 		
		encode(); 
	}

	QString destinationId() const 	{ return destinationIdS; }
	void setDestinationId( QString destinationId ) { 
		if ( !destinationIdSanityStore( destinationId ) )
			debugOutput(); 	
		encode(); 
	}

	QString senderId() const 	{ return senderIdS; }
	void setSenderId( QString senderId ) { 
		if ( senderIdSanityStore( senderId ) )
			debugOutput(); 		
		encode(); 
	}

	void setEncode( QString destinationId, QString senderId, QStringList dataFlags, QStringList data ) {
		QList<bool> success;
		success << destinationIdSanityStore( destinationId )
			<< senderIdSanityStore( senderId )
			<< dataFlagsSanityStore( dataFlags )
			<< dataSanityStore( data );

		// If a single sanity fails, output debug info
		for ( int c = 0; c < success.count(); ++c )
			if ( !success[c] )
				debugOutput();
		encode(); 
	}

private:
	QString packetS;
	QString destinationIdS;
	QString senderIdS;

	QStringList dataFlagsS;
	QStringList dataS;

	bool dataFlagsSanityStore( QStringList dataFlags );
	bool dataSanityStore( QStringList data );
	bool destinationIdSanityStore( QString destinationId );
	bool senderIdSanityStore( QString senderId );

	QRegExp dataCheck() const { return QRegExp("[:\\|]"); }
	QRegExp idCheck() const { return QRegExp("^Screen\\{[0-9]*\\}Inc\\{[0-9]*\\}$"); }

	QString errorName() const { return tr("Packet"); }

	// Called on encode/decode failure
	void debugOutput();

	void decode();
	void encode();

};

#endif

