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
XCBWindowManipulation::XCBWindowManipulation( QObject *parent ) : XCBWindowScanner( parent ) {
}

// Deconstructor **********************************************************************************
XCBWindowManipulation::~XCBWindowManipulation() {
}

// Window Shape ***********************************************************************************
void XCBWindowManipulation::resizeWindow( int windowID, QRect newSize ) {
	uint32_t values[] = { newSize.height(), newSize.width() };
	xcb_configure_window( serverConnection(), windowID, XCB_CONFIG_WINDOW_HEIGHT | XCB_CONFIG_WINDOW_WIDTH, values );
}

void XCBWindowManipulation::resizeWindow( int windowID, int width, int height ) {
	resizeWindow( windowID, QRect( 0, 0, width, height ) );
}

// Window Location ********************************************************************************
void XCBWindowManipulation::moveWindow( int windowID, int toScreen, QPoint toPoint ) {
	// TODO - Screen # Moving
	uint32_t values[] = { toPoint.x(), toPoint.y() };
	xcb_configure_window( serverConnection(), windowID, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, values );
}

void XCBWindowManipulation::moveWindow( int windowID, int toScreen, int x, int y ) {
	moveWindow( windowID, toScreen, QPoint( x, y ) );
}

// Focus Control **********************************************************************************
void XCBWindowManipulation::setUserFocus( int windowID ) {
	xcb_set_input_focus( serverConnection(), XCB_INPUT_FOCUS_PARENT, windowID, XCB_CURRENT_TIME );
}

// Border Control *********************************************************************************
void XCBWindowManipulation::setWindowBorder( int windowID, int width ) {
	uint32_t values[] = { width };
	xcb_configure_window( serverConnection(), windowID, XCB_CONFIG_WINDOW_BORDER_WIDTH, values );
}

