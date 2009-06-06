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

#include "win_windowmanipulation.h"

// Constructors ***********************************************************************************
WinWindowManipulation::WinWindowManipulation( QObject *parent ) : QObject( parent ) {
}

// Deconstructor **********************************************************************************
WinWindowManipulation::~WinWindowManipulation() {
}

// Window Shape ***********************************************************************************
void WinWindowManipulation::resizeWindow( HWND windowID, QRect newSize ) {
	SetWindowPos( windowID, HWND_TOP, 0, 0, newSize.width(), newSize.height(), SWP_NOMOVE | SWP_NOZORDER );
}

// Window Location ********************************************************************************
void WinWindowManipulation::moveWindow( HWND windowID, int toScreen, QPoint toPoint ) {
	// TODO - Screen # Moving
	SetWindowPos( windowID, HWND_TOP, toPoint.x(), toPoint.y(), 0, 0, SWP_NOSIZE | SWP_NOZORDER );
}

// Focus Control **********************************************************************************
void WinWindowManipulation::setUserFocus( HWND windowID ) {
	SetForegroundWindow( windowID );
}

// Border Control *********************************************************************************
void WinWindowManipulation::setWindowBorder( HWND windowID, int width ) {
	// TODO Add Functionality for border sizing
	if ( width <= 0 )
		// Remove Border and Title
		SetWindowLong(windowID, GWL_STYLE, (GetWindowLong(windowID, GWL_STYLE) & ~(WS_CAPTION | WS_SIZEBOX)));
	else 
		// Add Border and Title
		SetWindowLong(windowID, GWL_STYLE, (GetWindowLong(windowID, GWL_STYLE) | (WS_CAPTION | WS_SIZEBOX)));
}
