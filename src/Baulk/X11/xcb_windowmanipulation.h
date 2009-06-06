// Baulk - XCB Window Manipulator
//
// Baulk - Copyright (C) 2008-2009 - Jacob Alexander 
//   <haata at users.sf.net>
// Based off of code from Awesome WM 
//   (C) Julien Danjou <julien@danjou.info> 2007-2009
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

#ifndef __XCB_WINDOWMANIPULATOR_H
#define __XCB_WINDOWMANIPULATOR_H

#include <QObject>
#include <QPoint>
#include <QRect>
#include <QX11Info>

#include <xcb/xcb.h>
//#include <xcb/xcb_atom.h>
//#include <xcb/xcb_icccm.h>

#include "xcb_windowscanner.h"

//! Manipulates a window with convenient XCB functions
/*!
 * Convenience functions for manipulating windows
 * in a Tiling Environment under XCB
 */
class XCBWindowManipulation : public XCBWindowScanner {
	Q_OBJECT

public:
	// -- Constructors
	XCBWindowManipulation( QObject *parent );

	// -- Destructor
	~XCBWindowManipulation();

	// -- Accessors

	// -- Mutators
	void resizeWindow( xcb_window_t windowID, QRect newSize );
	void moveWindow( xcb_window_t windowID, int toScreen, QPoint toPoint );
	void setUserFocus( xcb_window_t windowID );
	void setWindowBorder( xcb_window_t windowID, int width );

	void setXCBConnection( xcb_connection_t *connection );

private:
	// -- Variables
	
	// -- Functions
};

#endif

