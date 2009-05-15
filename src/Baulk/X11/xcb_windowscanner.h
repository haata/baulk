// Baulk - XCB Window Scanner
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

#ifndef __XCB_WINDOWSCANNER_H
#define __XCB_WINDOWSCANNER_H

#include <QApplication>
#include <QDesktopWidget>
#include <QList>
#include <QObject>
#include <QX11Info>

#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>
#include <xcb/xcb_icccm.h>

typedef struct {
	xcb_window_t id;
	xcb_query_tree_cookie_t tree_cookie;
} root_win_t;

typedef struct {
	xcb_window_t id;
	int screen;
} windowInfo;

//! Scans Viewable X11 Windows for Window IDs
/*!
 * Uses XCB to Scan for available Window IDs
 * Also has functions to filter by Atom Strings
 */
class XCBWindowScanner : public QObject {
	Q_OBJECT

public:
	//! Default Constructor
	XCBWindowScanner( QObject *parent = 0 );

	//! Deconstructor
	~XCBWindowScanner();

	//-- Accessors
	//! Full list of useable Window IDs (castable to long)
	QList<windowInfo> fullList() const     { return availableIDs; }
	//! List filtered using filtering commands of Window IDs (castable to long)
	QList<windowInfo> filteredList() const { return filteredIDs; }

	//-- Helpers
	//! Prints the Atom String Information on the list of Windows
	void logPrintIDList( QList<windowInfo> list );
	
	//-- Mutators
	void resetFilteredList();
	void updateNumberOfScreens();

	//! RegExp Filter on Window Title Name (Visible)
	void regexFilterWindowName( QRegExp exp );

	//! RegExp Filter on the Name of the Window Icon (not always available)
	void regexFilterWindowIconName( QRegExp exp );

	//! RegExp Filter on the Hostname of the machine that owns the Window (usually the same, unless X over ssh)
	void regexFilterWindowMachineName( QRegExp exp );

	//! RegExp Filter on the Window Class Name (not user visible)
	void regexFilterWindowClass( QRegExp exp );

	//! RegExp Filter by Screen Number
	void regexFilterScreenNumber( QRegExp exp );

	//! Full Window ID rescan
	//!  Resets the filtered list as well
	void rescanWindowIDs();
private:
	//-- Variables
	xcb_connection_t *connection;
	int maxScreens;
	QList<windowInfo> availableIDs;
	QList<windowInfo> filteredIDs;

	//-- Functions
	void connectToX();
	
	//! Scans the Window IDs of the available windows
	void parseWindowIDs();

	/*! Get the QString value of an atom.
	 * \param windowID Window.
	 * \param atomType The atom.
	 * \return QString value on sucess, blank if not.
	 */
	QString windowAtomToString( xcb_window_t windowID, xcb_atom_t atomType );
};

#endif

