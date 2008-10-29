// Baulk - Control
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	control.cpp
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

#include "control.h"

BaulkControl::BaulkControl( QWidget *parent ) : BaulkWidget( parent ) {
	// Initialize Baulk Interface Dialog
	interfaceDialog = new BaulkInterfaceDialog( this );

	// Start Client if listen name is set
	connect( this, SIGNAL( serverListenNameSet( QString ) ), this, SLOT( startInformationClient() ) );

	// Main Layout Setup
	topVLayout = new QVBoxLayout;
	topHLayout = new QHBoxLayout;
	setLayout( topVLayout );
	topVLayout->addLayout( topHLayout );

	// Tab Layer
	tabLayer = new QStackedWidget;
	topHLayout->addWidget( tabLayer );

	// Dynamic Layout Setup
	dynTopLayout = new QSplitter( Qt::Horizontal );
	dynBotLayout = new QSplitter( Qt::Vertical );
	tabLayer->addWidget( dynTopLayout );
	dynTopLayout->addWidget( dynBotLayout );

	// Layout Property Setup
	topVLayout->setContentsMargins( 0,0,0,0 );
	topHLayout->setContentsMargins( 0,0,0,0 );
	dynTopLayout->setHandleWidth( 1 );
	dynBotLayout->setHandleWidth( 1 );

	loadLibraries();
	setupQActions();

	// Load Console Out
	int index = libraryList().name.lastIndexOf( QRegExp(".*BaulkStatus.*") );
	if ( index > -1 ) {
		loadMainWidget( libraryList().library[index] );
	}
}

// QAction Setup **********************************************************************************
void BaulkControl::setupQActions() {
	// Calls New Widget Dialog
	newWidget = new QAction( this );
	newWidget->setShortcut( tr("Alt+Meta+P") );
	connect( newWidget, SIGNAL( triggered() ), interfaceDialog, SLOT( newWidgetDialogLoader() ) );
	addAction( newWidget );
}

// Daemon Interaction *****************************************************************************
void BaulkControl::startInformationClient() {
	// Connection to the Daemon
	InformationClient *client = new InformationClient( serverListenName(), this );
	client->requestId();
	disconnect( this, SIGNAL( serverListenNameSet( QString ) ), this, SLOT( startInformationClient() ) );
}

// Dynamic Libraries ******************************************************************************
void BaulkControl::loadLibraries() {
	QStringList libraryList = LibraryLoader( this ).loadableLibraries();

	for ( int c = 0; c < libraryList.count(); ++c ) {
		if ( !libraryList[c].contains("BaulkControl") ) {
			QString libName = libraryList[c];
			LibraryLoader *library = new LibraryLoader( this );
			library->loadLibrary( libName );

			// Prevent unbalanced lists
			if ( libList.name.count() != libList.library.count() )
				qFatal( tr("BaulkControl\n\tLibList lengths do not match\n\tName: %1\n\tLibrary: %2")
						.arg( libList.name.count() )
						.arg( libList.library.count() )
					.toUtf8() );

			// Prevent Duplicates
			if ( !libList.name.contains( libName ) ) {
				libList.name << libName;
				libList.library << library;
			}
		}
	}
}

void BaulkControl::loadMainWidget( LibraryLoader *library ) {
	// Loads the primary widget of a libray
	BaulkWidget *widget = library->loadBaulkWidget( "mainWidget", this );
	dynBotLayout->addWidget( widget );
}

