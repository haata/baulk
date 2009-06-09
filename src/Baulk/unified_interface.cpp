// Baulk - Unified Interface
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

#include "unified_interface.h"

// Constructors ***********************************************************************************
//-CMAKE UnifiedInterface::UnifiedInterface( QObject *parent ) : WinWindowManipulation( parent ) : WinWindowScanner( parent ) { //-WIN
UnifiedInterface::UnifiedInterface( QObject *parent ) : XCBWindowManipulation( parent ) { //-X11
}

// Destructor *************************************************************************************
UnifiedInterface::~UnifiedInterface() {
}

// Window Tiling Commands *************************************************************************
void UnifiedInterface::swapWindows( int windowID1, int windowID2 ) {
	// Procedure
	//  - Check Sizes of two windows
	//  - Create contigency if the window cannot resize (too small or to big)
	//  - Move windows into place
	QString window1 = windowSizeInfo( windowID1 );
	QString window2 = windowSizeInfo( windowID2 );

	// Attempt to resize
	resizeWindow( windowID1, windowWidth( window2 ), windowHeight( window2 ) );
	resizeWindow( windowID2, windowWidth( window1 ), windowHeight( window1 ) );

	// Check new window size
	QString window1Check = windowSizeInfo( windowID1 );
	QString window2Check = windowSizeInfo( windowID2 );

	// Window1 too big, ie. cannot get as small as desired
	if ( windowWidth( window1Check ) > windowWidth( window2 ) || windowHeight( window1Check ) > windowHeight( window2 ) ) {
		qDebug("Window 1 is too Big!! Cannot resize to desired small size.");
		// TODO Contingency
	}

	// Window2 too big, ie. cannot get as small as desired
	if ( windowWidth( window2Check ) > windowWidth( window1 ) || windowHeight( window2Check ) > windowHeight( window1 ) ) {
		qDebug("Window 2 is too Big!! Cannot resize to desired small size.");
		// TODO Contingency
	}

	// Move Windows to desired spots
	// TODO Handle Different Screens
	int screen1 = 0;
	int screen2 = 0;

	moveWindow( windowID1, screen1, windowRelativeX( window2 ), windowRelativeY( window2 ) );
	moveWindow( windowID2, screen2, windowRelativeX( window1 ), windowRelativeY( window1 ) );
}

void UnifiedInterface::tileIDList( QStringList windowIDList, bool horizontal, QRect area ) {
	// Proposed Tiling
	//  - Calculate size for each window, either Vertical or Horizontal
	//  - Attempt to resize each window
	//  - Check if window resized correctly, if not, re-adjust other windows to fit around P.i.t.A. windows in the given area
	//  - If this is not possible, (decide float, cover over with other windows, etc. [probably should make this an option] )
	//  - Move windows to decided locations
	QRect windowRect;
	int usedLength = 0;
	int screen = 0; // TODO Make Setting

	horizontal 
		// Horizontal Tiling
		? windowRect.setRect( 0, 0, area.width() / windowIDList.count(), area.height() )
		// Vertical Tiling
		: windowRect.setRect( 0, 0, area.width(), area.height() / windowIDList.count() );

	// Attempt to resize, Check Size (and fix if necessary), then Move
	for ( int c = 0; c < windowIDList.count(); ++c ) {
		int windowID = listStringToWindowID( windowIDList[c] );

		// Attempt Window Resize
		resizeWindow( windowID, windowRect );


	// TODO
		// Check Size
		// Fix
		QRect newWindowRect = windowRect;
	// TODO


		// Move Window
		horizontal 
			// Horizontal Tiling
			? moveWindow( windowID, screen, area.left() + usedLength, area.top() )
			// Vertical Tiling
			: moveWindow( windowID, screen, area.left(), area.top() + usedLength );

		// Next Window Move
		usedLength += horizontal
			// Horizontal Tiling
			? newWindowRect.width()
			// Vertical Tiling
			: newWindowRect.height();
	}
}

void UnifiedInterface::tileIDList( QStringList windowIDList, bool horizontal, int x, int y, int width, int height ) {
	tileIDList( windowIDList, horizontal, QRect( x, y, width, height ) );
}

// Window Borders *********************************************************************************
void UnifiedInterface::setWindowBorders( QStringList windowIDList, int width ) {
	for ( int c = 0; c < windowIDList.count(); ++c )
		setWindowBorder( listStringToWindowID( windowIDList[c] ), width );
}

