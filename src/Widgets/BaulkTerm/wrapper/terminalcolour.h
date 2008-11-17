// BaulkTerm - Terminal Colour Container
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

/**
 * @author Jacob Alexander (HaaTa)
 *
 * A container for Terminal Colours
 *
 * Contains, QColor, transparency bool, and bold bool
 */

#ifndef __TERMINALCOLOUR_H
#define __TERMINALCOLOUR_H

#include <QColor>
#include <QString>
#include <QStringList>
#include <QVariant>

class TerminalColour {
public:
	// Constructors
	TerminalColour();
	TerminalColour( QColor useColour, bool useTransparency, bool useBold );

	// Colour
	QColor colour() const;
	void setColour( QColor useColour );

	// Bold
	bool bold() const;
	void setBold( bool useBold );

	// Transparency
	bool transparency() const;
	void setTransparency( bool useTransparency );

	// Encompassing
	QString toString() const;
	QVariant toVariant() const;
	void setOptions( QColor useColour, bool useTransparency, bool useBold );
	void setFromString( QString config );
	void setFromVariant( QVariant config );

private:
	QColor colourStore;

	bool boldStore;
	bool transparencyStore;
};

#endif

