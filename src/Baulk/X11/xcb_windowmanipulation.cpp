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

#include "xcb_windowmanipulation.h"

// Constructors ***********************************************************************************
XCBWindowManipulation::XCBWindowManipulation( QObject *parent ) : QObject( parent ) {
}

XCBWindowManipulation::XCBWindowManipulation( xcb_connection_t *connection, QObject *parent ) : QObject( parent ) {
}

// Deconstructor **********************************************************************************
XCBWindowManipulation::~XCBWindowManipulation() {
}

// XCB Setup **************************************************************************************
void XCBWindowManipulation::setXCBConnection( xcb_connection_t *connection ) {
	server_connection = connection;
}

// Window Shape ***********************************************************************************
void XCBWindowManipulation::resizeWindow( xcb_window_t windowID, QRect newSize ) {
}

// Window Location ********************************************************************************
void XCBWindowManipulation::moveWindow( xcb_window_t windowID, int toScreen, QPoint toPoint ) {
}

// Focus Control **********************************************************************************
void XCBWindowManipulation::setUserFocus( xcb_window_t windowID ) {
}




