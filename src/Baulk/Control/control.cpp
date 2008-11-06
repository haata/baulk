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

// Constructors ***********************************************************************************
BaulkControl::BaulkControl( QWidget *parent ) : BaulkWidget( parent ) {
	// Initialize Baulk Interface Dialog
	interfaceDialog = new BaulkInterfaceDialog( this );

	// Initialize BaulkXML for Config Loading/Saving
	xmlConfig = new BaulkXML( "BaulkControl", this );

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

	// Set Index Fallback default
	lastKnownGoodIndex = -1;

	// Load Console Out
	int index = libraryList().name.lastIndexOf( QRegExp(".*BaulkStatus.*") );
	if ( index > -1 ) 
		loadMainWidget( libraryList().library[index] );

	// Save BaulkXML Config
	xmlConfig->saveConfig();
}

// QAction ****************************************************************************************
// ** Setup
void BaulkControl::setupQActions() {
	// ** Dialog Hotkeys

	// Calls New Widget Dialog
	connect( addGlobalAction( tr("New Widget Dialog"), tr("Alt+Meta+P"), true ), SIGNAL( triggered() ), 
		interfaceDialog, SLOT( newWidgetDialogLoader() ) );

	// Calls Hotkey Dialog
	connect( addGlobalAction( tr("Available Actions Dialog"), tr("Alt+Meta+O") ),
		SIGNAL( triggered() ), interfaceDialog, SLOT( actionsDialogLoader() ) );


	// ** Tile Manipulation Hotkeys
	
	// Shifts Focus Down
	connect( addGlobalAction( tr("Shift Focus Down"), tr("Alt+Meta+J") ),
		SIGNAL( triggered() ), this, SLOT( focusDown() ) );

	// Shifts Focus Left
	connect( addGlobalAction( tr("Shift Focus Right"), tr("Alt+Meta+L") ),
		SIGNAL( triggered() ), this, SLOT( focusRight() ) );

	// Shifts Focus Right
	connect( addGlobalAction( tr("Shift Focus Left"), tr("Alt+Meta+H") ),
		SIGNAL( triggered() ), this, SLOT( focusLeft() ) );

	// Shifts Focus Up
	connect( addGlobalAction( tr("Shift Focus Up"), tr("Alt+Meta+K") ),
		SIGNAL( triggered() ), this, SLOT( focusUp() ) );
	
	// Swaps Layout Direction on the Bottom Layout
	connect( addGlobalAction( tr("Orientation Swap Bottom Layout"), tr("Alt+Meta+Space") ), 
		SIGNAL( triggered() ), this, SLOT( swapOrientationBot() ) );

	// Swaps Layout Direction on the Top Layout
	connect( addGlobalAction( tr("Orientation Swap Top Layout"), tr("Alt+Meta+Z") ),
		SIGNAL( triggered() ), this, SLOT( swapOrientationTop() ) );

	// Remove Focused Widget
	connect( addGlobalAction( tr("Remove Widget"), tr("Alt+Meta+C") ),
		SIGNAL( triggered() ), this, SLOT( removeWidget() ) );

	// Move Widget Down
	connect( addGlobalAction( tr("Move Widget Down"), tr("Alt+Shift+J") ),
		SIGNAL( triggered() ), this, SLOT( moveDown() ) );

	// Move Widget Left
	connect( addGlobalAction( tr("Move Widget Left"), tr("Alt+Shift+H") ),
		SIGNAL( triggered() ), this, SLOT( moveLeft() ) );

	// Move Widget Right
	connect( addGlobalAction( tr("Move Widget Right"), tr("Alt+Shift+L") ),
		SIGNAL( triggered() ), this, SLOT( moveRight() ) );

	// Move Widget Up
	connect( addGlobalAction( tr("Move Widget Up"), tr("Alt+Shift+K") ),
		SIGNAL( triggered() ), this, SLOT( moveUp() ) );

}

// ** Add Action to Global List
QAction *BaulkControl::addGlobalAction( QString title, QString keyShortcut, bool globalConnect ) {
	// Check Config for Hotkey
	QString key = xmlConfig->option( "hotkey", "name", QVariant( title ), false ).toString();
	if ( key == "" ) {
		key = keyShortcut;
		xmlConfig->setOption( "hotkey", QVariant( key ), "name", QVariant( title ) );
	}

	// Setup Hotkey
	QAction *action = new QAction( title, this );
	action->setShortcut( key );
	addAction( action );
	glbQActions << action;

	if ( globalConnect )
		connect( action, SIGNAL( triggered() ), this, SLOT( globalActionTriggered() ) );

	return action;
}

// ** Modify Shortcut Key
void BaulkControl::modifyGlobalKeyShortcut( int key, QString keyShortcut ) {
	// Change Shortcut Key
	glbQActions[key]->setShortcut( keyShortcut );

	// Save Setting to Config
	xmlConfig->setOption( "hotkey", QVariant( keyShortcut ), "name", QVariant( glbQActions[key]->text() ) );
	xmlConfig->saveConfig();
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
			LibraryLoader *library = new LibraryLoader( libName, this );

			// Prevent unbalanced lists
			if ( libList.name.count() != libList.library.count() )
				qFatal( tr("%1\n\tLibList lengths do not match\n\tName: %2\n\tLibrary: %3")
						.arg( errorName() )
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

	// Focus Index
	int index = lastKnownGoodIndex < dynBotLayout->count() ? lastKnownGoodIndex + 1 : 0;

	// Do not use a focus index if it does not exist
	if ( index >= dynBotLayout->count() - 1 )
		index = dynBotLayout->count() - 1;

	// Set Widget Focus
	if ( dynBotIndex() == 0 && index == -1 )
		dynBotLayout->widget( 0 )->setFocus();
	else dynBotLayout->widget( index )->setFocus();
}

// Tile Manipulation Control **********************************************************************
// ** Orientation
void BaulkControl::swapOrientationBot() { 
	switch ( dynBotLayout->orientation() ) {
	case Qt::Horizontal:
		dynBotLayout->setOrientation( Qt::Vertical );
		break;
	case Qt::Vertical:
		dynBotLayout->setOrientation( Qt::Horizontal );
		break;
	default:
		qCritical( tr("%1\n\tInvalid Orientation, Bottom Layout").arg( errorName() ).toUtf8() );
		break;
	}
}

void BaulkControl::swapOrientationTop() {
	switch ( dynTopLayout->orientation() ) {
	case Qt::Horizontal:
		dynTopLayout->setOrientation( Qt::Vertical );
		break;
	case Qt::Vertical:
		dynTopLayout->setOrientation( Qt::Horizontal );
		break;
	default:
		qCritical( tr("%1\n\tInvalid Orientation, Top Layout").arg( errorName() ).toUtf8() );
		break;
	}
}

// ** Focus Control
//  Note: Incrementing the coordinate is only needed on max value cases due to how Qt
//  	calculates max x and y, see Qt docs for more details
void BaulkControl::focusDec() {
	int curPos = dynBotIndex();

	// Boundary Case
	if( curPos == 0 )
		return;

	// Decrement Focus
	dynBotLayout->widget( curPos - 1 )->setFocus();
}

void BaulkControl::focusDown() {
	switch ( dynBotLayout->orientation() ) {
	case Qt::Horizontal:
		// If Layout is Horizontal/Horizontal then do nothing
		switch ( dynTopLayout->orientation() ) {
		case Qt::Vertical:
			focusLayoutInc();
			break;
		default:
			break;
		}
		break;
	case Qt::Vertical:
		focusInc();
		break;
	default:
		qCritical( tr("%1\n\tInvalid Orientation, Focus Down").arg( errorName() ).toUtf8() );
		break;
	}
}

void BaulkControl::focusInc() {
	int curPos = dynBotIndex();

	// Boundary Case
	if( curPos == dynBotLayout->count() - 1 )
		return;

	// Increment Focus
	dynBotLayout->widget( curPos + 1 )->setFocus();
}

void BaulkControl::focusLayoutDec() {
	int curPos = dynBotIndex();
	int curLayoutPos = dynTopLayout->indexOf( dynBotLayout );

	// Boundary Case
	if ( curLayoutPos == 0 )
		return;

	// Decrement Layout
	dynBotLayout = qobject_cast<QSplitter*>( dynTopLayout->widget( curLayoutPos - 1 ) );

	// Set Focus
	if ( curPos >=  dynBotLayout->count() )
		curPos = dynBotLayout->count() - 1;
	dynBotLayout->widget( curPos )->setFocus();
}

void BaulkControl::focusLayoutInc() {
	int curPos = dynBotIndex();
	int curLayoutPos = dynTopLayout->indexOf( dynBotLayout );

	// Boundary Case
	if ( curLayoutPos == dynTopLayout->count() - 1 )
		return;

	// Increment Layout
	dynBotLayout = qobject_cast<QSplitter*>( dynTopLayout->widget( curLayoutPos + 1 ) );

	// Set Focus
	if ( curPos >=  dynBotLayout->count() )
		curPos = dynBotLayout->count() - 1;
	dynBotLayout->widget( curPos )->setFocus();
}

void BaulkControl::focusLeft() {
	switch ( dynBotLayout->orientation() ) {
	case Qt::Horizontal:
		focusDec();
		break;
	case Qt::Vertical: 
		// If Layout is Vertical/Vertical then do nothing
		switch ( dynTopLayout->orientation() ) {
		case Qt::Horizontal:
			focusLayoutDec();
			break;
		default:
			break;
		}
		break;
	default:
		qCritical( tr("%1\n\tInvalid Orientation, Focus Left").arg( errorName() ).toUtf8() );
		break;
	}
}

void BaulkControl::focusRight() {
	switch ( dynBotLayout->orientation() ) {
	case Qt::Horizontal:
		focusInc();
		break;
	case Qt::Vertical: 
		// If Layout is Vertical/Vertical then do nothing
		switch ( dynTopLayout->orientation() ) {
		case Qt::Horizontal:
			focusLayoutInc();
			break;
		default:
			break;
		}
		break;
	default:
		qCritical( tr("%1\n\tInvalid Orientation, Focus Right").arg( errorName() ).toUtf8() );
		break;
	}
}

void BaulkControl::focusUp() {
	switch ( dynBotLayout->orientation() ) {
	case Qt::Horizontal:
		// If Layout is Horizontal/Horizontal then do nothing
		switch ( dynTopLayout->orientation() ) {
		case Qt::Vertical:
			focusLayoutDec();
			break;
		default:
			break;
		}
		break;
	case Qt::Vertical:
		focusDec();
		break;
	default:
		qCritical( tr("%1\n\tInvalid Orientation, Focus Up").arg( errorName() ).toUtf8() );
		break;
	}
}

// ** Widget Removal
void BaulkControl::removeWidget() {
	int curPos = dynBotIndex();
	int curBotLayout = dynTopIndex();
	QWidget *widget = dynBotLayout->widget( curPos );

	// Remove the Widget completely from the layout
	widget->hide();
	topVLayout->addWidget( widget );
	widget->close();

	// No more Widgets in bottom layout
	if ( dynBotLayout->count() == 0 ) {
		// Do not close the last dynBotLayout
		bool lastLayout = true;
		if ( dynTopLayout->count() > 1 ) {
			dynTopLayout->widget( curBotLayout )->close();
			lastLayout = false;
		}

		// Set Focus after removing dynBotLayout
		if ( dynTopLayout->count() != 0 ) {
			int index = dynTopLayout->count() != 1 ? curBotLayout - 1 : 0;
			dynBotLayout = qobject_cast<QSplitter*>( dynTopLayout->widget( index ) ); 
			if ( dynBotLayout->count() > 0 )
				dynBotLayout->widget( 0 )->setFocus();
		}

		// Load Default Widget if all all closed
		if ( lastLayout ) {
			int index = libraryList().name.lastIndexOf( QRegExp(".*BaulkStatus.*") );
			if ( index > -1 ) 
				loadMainWidget( libraryList().library[index] );
		}
	}
	else {
		// Set the focus to the same index if available, else use the last widget
		if ( curPos + 1 <= dynBotLayout->count() )
			dynBotLayout->widget( curPos )->setFocus();
		else dynBotLayout->widget( dynBotLayout->count() - 1 )->setFocus();
	}
}

// ** Widget Moving
void BaulkControl::moveDec() {
}

void BaulkControl::moveDown() {
	switch ( dynBotLayout->orientation() ) {
	case Qt::Horizontal:
		// If Layout is Horizontal/Horizontal then do nothing
		switch ( dynTopLayout->orientation() ) {
		case Qt::Vertical:
			moveLayoutInc();
			break;
		default:
			break;
		}
		break;
	case Qt::Vertical:
		moveInc();
		break;
	default:
		qCritical( tr("%1\n\tInvalid Orientation, Move Down").arg( errorName() ).toUtf8() );
		break;
	}
}

void BaulkControl::moveInc() {
}

void BaulkControl::moveLayoutDec() {
}

void BaulkControl::moveLayoutInc() {
}

void BaulkControl::moveLeft() {
	switch ( dynBotLayout->orientation() ) {
	case Qt::Horizontal:
		moveDec();
		break;
	case Qt::Vertical: 
		// If Layout is Vertical/Vertical then do nothing
		switch ( dynTopLayout->orientation() ) {
		case Qt::Horizontal:
			moveLayoutDec();
			break;
		default:
			break;
		}
		break;
	default:
		qCritical( tr("%1\n\tInvalid Orientation, Move Left").arg( errorName() ).toUtf8() );
		break;
	}
}

void BaulkControl::moveRight() {
	switch ( dynBotLayout->orientation() ) {
	case Qt::Horizontal:
		moveInc();
		break;
	case Qt::Vertical: 
		// If Layout is Vertical/Vertical then do nothing
		switch ( dynTopLayout->orientation() ) {
		case Qt::Horizontal:
			moveLayoutInc();
			break;
		default:
			break;
		}
		break;
	default:
		qCritical( tr("%1\n\tInvalid Orientation, Move Right").arg( errorName() ).toUtf8() );
		break;
	}
}

void BaulkControl::moveUp() {
	switch ( dynBotLayout->orientation() ) {
	case Qt::Horizontal:
		// If Layout is Horizontal/Horizontal then do nothing
		switch ( dynTopLayout->orientation() ) {
		case Qt::Vertical:
			moveLayoutDec();
			break;
		default:
			break;
		}
		break;
	case Qt::Vertical:
		moveDec();
		break;
	default:
		qCritical( tr("%1\n\tInvalid Orientation, Move Up").arg( errorName() ).toUtf8() );
		break;
	}
}

// Widget Finders *********************************************************************************
int BaulkControl::dynBotIndex() {
	// Search through Current Bottom Layout First
	for ( int count = 0; count < dynBotLayout->count(); ++count )
		if ( dynBotLayout->widget( count )->hasFocus() ) 
			return count;

	// Search through all App Widgets as a bonus this will fix column focus
	for ( int cur = 0; cur < dynTopLayout->count(); ++cur ) {
		dynBotLayout = qobject_cast<QSplitter*>( dynTopLayout->widget( cur ) );
		for ( int count = 0; count < dynBotLayout->count(); ++count )
			if ( dynBotLayout->widget( count )->hasFocus() )
				return count;
	}

	return 0;
}

int BaulkControl::dynTopIndex() {
	// Search through all the dynBotLayouts for the current one
	for ( int count = 0; count < dynTopLayout->count(); ++count )
		if( dynBotLayout == qobject_cast<QSplitter*>( dynTopLayout->widget( count ) ) )
			return count;
	
	return 0;
}

// Assistive Functions
void BaulkControl::globalActionTriggered() {
	// Keeps track of the last widget focus
	lastKnownGoodIndex = dynBotIndex();
}

// Reimplemented Functions ************************************************************************
void BaulkControl::closeEvent( QCloseEvent *event ) {
}

