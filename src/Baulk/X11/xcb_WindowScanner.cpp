// Baulk - XCB Window Scanner
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
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

#include "xcb_WindowScanner.h"

// Constructors ***********************************************************************************
XCBWindowScanner::XCBWindowScanner( QObject *parent ) : QObject( parent ) {
	parseWindowIDs();
}

// Deconstructor **********************************************************************************
XCBWindowScanner::~XCBWindowScanner() {
}

// Atom Operations ********************************************************************************
QString XCBWindowScanner::windowAtomToString( xcb_connection_t *conn, xcb_window_t w, xcb_atom_t atom ) {
	xcb_atom_t COMPOUND_TEXT = 0;
	xcb_atom_t UTF8_STRING = 0;

	xcb_get_text_property_reply_t reply;
	memset( &reply, 0, sizeof ( reply ) * 1 );

	if ( !xcb_get_text_property_reply( conn, xcb_get_text_property_unchecked( conn, w, atom ), &reply, NULL) 
			|| !reply.name_len 
			|| reply.format != 8 ) {
		xcb_get_text_property_reply_wipe( &reply );
		qWarning("Problem checking atom string");
		return "";
	}

	/* Check whether the returned property value is just an ascii
	 * string, an UTF-8 string or just some random multibyte in any other
	 * encoding. 
	 */
	QString text = "";
	if( reply.encoding == STRING 
			|| reply.encoding == UTF8_STRING 
			|| reply.encoding == COMPOUND_TEXT) {
		text = reply.name;
	}
	else qWarning("Invalid encoding on atom string");

	xcb_get_text_property_reply_wipe( &reply );

	// Remove garbage characters from the end of the string
	text.resize( (int)reply.name_len );

	return text;
}

// Window ID Parsing ******************************************************************************
void XCBWindowScanner::parseWindowIDs() {
	// Connect to X Server through XCB
	xcb_connection_t *connection = xcb_connect(NULL, 0 /* Default Screen, TODO Either config or detect from X11 int */ );
	if ( xcb_connection_has_error( connection ) )
		qCritical("Cannot open display");

	// Declarations
	int i, phys_screen, tree_c_len;
	const int screen_max = QApplication::desktop()->numScreens();
	root_win_t root_wins[screen_max];
	xcb_query_tree_reply_t *tree_r;
	xcb_window_t *wins = NULL;
	xcb_get_window_attributes_reply_t *attr_r;

	// Scan the Available screens for Root IDs and Window Trees
	for ( phys_screen = 0; phys_screen < screen_max; phys_screen++ ) {
		// Get the root window ID associated to this screen
		root_wins[phys_screen].id = (xcb_window_t)QX11Info::appRootWindow( phys_screen );

		// Get the window tree associated to this screen
		root_wins[phys_screen].tree_cookie = xcb_query_tree_unchecked( connection, root_wins[phys_screen].id );
	}

	// Operate on the found Root Window Trees per each screen
	//  - Find the Window Tree
	//  - Get the attributes for each Window
	//  - Determine if each Window is tileable
	//  - Process useable Windows
	for ( phys_screen = 0; phys_screen < screen_max; phys_screen++ ) {
		tree_r = xcb_query_tree_reply( connection, root_wins[phys_screen].tree_cookie, NULL );

		// Tree Invalid
		if( !tree_r )
			continue;

		// Get the tree of the children windows of the current root window
		if( !( wins = xcb_query_tree_children( tree_r ) ) )
			qCritical("cannot get tree children");
		tree_c_len = xcb_query_tree_children_length( tree_r );
		xcb_get_window_attributes_cookie_t attr_wins[tree_c_len];

		// Find Window Attributes
		for ( i = 0; i < tree_c_len; i++ )
			attr_wins[i] = xcb_get_window_attributes_unchecked( connection, wins[i] );

		// Determine if window is tileable
		bool *windowCheckSuccess = new bool[tree_c_len];
		for ( i = 0; i < tree_c_len; ++i ) {
			attr_r = xcb_get_window_attributes_reply( connection, attr_wins[i], NULL );

			// Window not tileable
			if ( !attr_r 
					|| attr_r->map_state != XCB_MAP_STATE_VIEWABLE 
					|| attr_r->override_redirect ) {
				windowCheckSuccess[i] = false;
				delete attr_r;
				continue;
			}

			windowCheckSuccess[i] = true;
			delete attr_r;
		}

		// Tile Each Window
		for ( i = 0; i < tree_c_len; ++i ) {
			// Window Viewable Check
			if ( !windowCheckSuccess[i] )
				continue;

			// Window INFO
			qDebug( tr("Win#: %1  Screen: %2  Window ID: %3").arg( i ).arg( phys_screen ).arg( (long)wins[i] ).toUtf8() );
			qDebug( windowAtomToString( connection, wins[i], WM_NAME ).toUtf8() ); // Visible name, often is dynamic...
			qDebug( windowAtomToString( connection, wins[i], WM_ICON_NAME ).toUtf8() ); // Not always available
			qDebug( windowAtomToString( connection, wins[i], WM_CLIENT_MACHINE ).toUtf8() );
			qDebug( windowAtomToString( connection, wins[i], WM_CLASS ).toUtf8() ); // Hidden app name, usually useful
		}

		delete tree_r;
	}
}

