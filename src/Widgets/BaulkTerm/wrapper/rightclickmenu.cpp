// Baulk - BaulkTerm Right Click Menu
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

#include "rightclickmenu.h"

// Constructor ************************************************************************************
BaulkTermRightClickMenu::BaulkTermRightClickMenu( QWidget *parent ) : QMenu( parent ) {
	// Menu Settings
	setStyleSheet("QWidget {"
				"background: grey;"
				"}");

	// Initialize Actions
	copyAction = new QAction( tr("Copy"), this );
	fontAction = new QAction( tr("Set Font"), this );
	pasteAction = new QAction( tr("Paste"), this );

	// Attach Actions
	addAction( copyAction );
	addAction( pasteAction );
	addSeparator();
	addAction( fontAction );

	// Connections
	connect( fontAction, SIGNAL( triggered() ), SLOT( fontDialog() ) );
}

// Fonts ******************************************************************************************
void BaulkTermRightClickMenu::fontDialog() {
	bool ok;

	// Font Dialog
	QFont font = QFontDialog::getFont( &ok, QFont( "Monospace", 10 ), this );

	if ( ok )
		emit newFont( font );
}

