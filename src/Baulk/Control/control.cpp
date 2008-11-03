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
	connect( addGlobalAction( tr("New Widget Dialog"), tr("Alt+Meta+P") ), SIGNAL( triggered() ), 
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
}

// ** Add Action to Global List
QAction *BaulkControl::addGlobalAction( QString title, QString keyShortcut ) {
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
	widget->setFocus();
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
void BaulkControl::focusDown() {
	QRect widgetFocus = focusWidget()->geometry();
	QPoint search = mapFromParent( QPoint( widgetFocus.width() / 2, widgetFocus.bottom() ) );
	search.ry() = search.ry() + 3;

	QWidget *widget = childAt( search );
	// If no widget can be found, don't switch focus
	if ( widget != 0 ) 
		widget->setFocus();

	qDebug( QString("Down - x: %1, y: %2").arg( search.x() ).arg( search.y() ).toUtf8() );
}

void BaulkControl::focusLeft() {
	QRect widgetFocus = focusWidget()->geometry();
	QPoint search = mapFromParent( QPoint( 0, widgetFocus.height() / 2 ) );

	QWidget *widget = childAt( search );
	// If no widget can be found, don't switch focus
	if ( widget != 0 )
		widget->setFocus();

	qDebug( QString("Left - x: %1, y: %2").arg( search.x() ).arg( search.y() ).toUtf8() );
}

void BaulkControl::focusRight() {
	QRect widgetFocus = focusWidget()->geometry();
	QPoint search = mapFromParent( QPoint( widgetFocus.right(), widgetFocus.height() / 2 ) );
	search.rx() = search.rx() + 3;

	QWidget *widget = childAt( search );
	// If no widget can be found, don't switch focus
	if ( widget != 0 )
		widget->setFocus();

	qDebug( QString("Right - x: %1, y: %2").arg( search.x() ).arg( search.y() ).toUtf8() );
}

void BaulkControl::focusUp() {
	QRect widgetFocus = focusWidget()->geometry();
	QPoint search = mapFromParent( QPoint( widgetFocus.width() / 2, 0 ) );

	QWidget *widget = childAt( search );
	// If no widget can be found, don't switch focus
	if ( widget != 0 )
		widget->setFocus();

	qDebug( QString("Up - x: %1, y: %2").arg( search.x() ).arg( search.y() ).toUtf8() );
}

// Reimplemented Functions ************************************************************************
void BaulkControl::closeEvent( QCloseEvent *event ) {
}

