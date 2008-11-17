// Baulk - Terminal Colour Container
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

#include "terminalcolour.h"

// Constructors ***********************************************************************************
TerminalColour::TerminalColour() {
	colourStore = QColor( "#000000" );
	transparencyStore = false;
	boldStore = false;
}

TerminalColour::TerminalColour( QColor useColour, bool useTransparency, bool useBold ) {
	setOptions( useColour, useTransparency, useBold );
}

// Colour *****************************************************************************************
QColor TerminalColour::colour() const {
	return colourStore;
}

void TerminalColour::setColour( QColor useColour ) {
	colourStore = useColour;
}

// Transparency ***********************************************************************************
bool TerminalColour::transparency() const {
	return transparencyStore;
}

void TerminalColour::setTransparency( bool useTransparency ) {
	transparencyStore = useTransparency;
}

// Bold *******************************************************************************************
bool TerminalColour::bold() const {
	return boldStore;
}

void TerminalColour::setBold( bool useBold ) {
	boldStore = useBold;
}

// Encompassing ***********************************************************************************
QString TerminalColour::toString() const {
	return QString("%1,%2,%3").arg( colour().name() ).arg( transparency() ).arg( bold() );
}

QVariant TerminalColour::toVariant() const {
	return QVariant( toString() );
}

void TerminalColour::setOptions( QColor useColour, bool useTransparency, bool useBold ) {
	colourStore = useColour;
	transparencyStore = useTransparency;
	boldStore = useBold;
}

void TerminalColour::setFromString( QString config ) {
	QStringList args = config.split(",");
	colourStore = QColor( args[0] );
	transparencyStore = args[1].toInt();
	boldStore = args[2].toInt();
}

void TerminalColour::setFromVariant( QVariant config ) {
	setFromString( config.toString() );
}

