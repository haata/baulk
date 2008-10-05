// Baulk
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	baulk.cpp
//  Author(s):	Jacob Alexander (HaaTa)
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

#include "baulk.h"

// Constructor
Baulk::Baulk( QWidget *parent ) : QMainWindow( parent ) {
	LibraryLoader *library = new LibraryLoader( this );
	if ( library->exists("BaulkServer") && library->exists("BaulkClient") ) {
		// TODO - Start Server
	}
	
	// Window Settings
	setWindowTitle("Baulk - STATIC TITLE");
	setAttribute( Qt::WA_DeleteOnClose );

	// Setup Controller Instance
	library = new LibraryLoader( this );
	library->loadLibrary( "BaulkControl" ); // TODO Add Version Control
	controller = ( (QWidget*(*)( QWidget* )) library->lrResolve("new_widget") )( this ); // TODO Use Correct Symbol
	setCentralWidget( controller );	
}

// Window Close Event
void Baulk::closeEvent( QCloseEvent *event ) {
	//event->ignore();
	qDebug("Closing");
	event->accept();
}

