// Baulk - Windows Window Manipulator
//
// Baulk - Copyright (C) 2008-2009 - Jacob Alexander 
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

#ifndef __WIN_WINDOWMANIPULATOR_H
#define __WIN_WINDOWMANIPULATOR_H

#include <QObject>
#include <QPoint>
#include <QRect>

#include <windows.h>

//! Manipulates a window with convenient Windows functions
/*!
 * Convenience functions for manipulating windows
 * in a Tiling Environment under Windows
 */
class WinWindowManipulation : public QObject {
	Q_OBJECT

public:
	// -- Constructors
	WinWindowManipulation( QObject *parent );

	// -- Destructor
	~WinWindowManipulation();

	// -- Mutators
	void resizeWindow( HWND windowID, QRect newSize );
	void moveWindow( HWND windowID, int toScreen, QPoint toPoint );
	void setUserFocus( HWND windowID );
	void setWindowBorder( HWND windowID, int width );

private:
	// -- Variables
	
	// -- Functions
};

#endif

