// Baulk - qtermwidget Reimplement - BaulkTerm
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

#include "baulkterm.h"

// Constructors ***********************************************************************************
BaulkTerm::BaulkTerm( int startNow, QWidget *parent ) : BaulkWidget( parent ) {
	// Tab Bar
	tabBar = new QTabBar( this );
	if ( !useTabBar )
		tabBar->hide();

	tabLayer = new QStackedWidget;

	// Initialize BaulkXML for Config Loading/Saving
	xmlConfig = new BaulkXML( "BaulkTerm", this );

	// term Settings
	configurationDefaults();
	configurationLoad();

	// Initial Terminal
	startPriority = startNow;
	newTab();

	// Layout
	layout = new QVBoxLayout;
	layout->setContentsMargins( 0,0,0,0 );

	layout->addWidget( tabBar );

	layout->addWidget( tabLayer );

	// Widget Settings
	setFocusProxy( term );
	setLayout( layout );

	// Connections
	connect( term, SIGNAL( finished() ), this, SIGNAL( finished() ) );
	connect( term, SIGNAL( finished() ), this, SLOT( closeTab() ) );
}

// Configuration **********************************************************************************
void BaulkTerm::configurationDefaults() {
	// Font
	font = QFont( "Terminus" );
	font.setPointSize( 12 );

	// Transparency
	opacity = 0.7;		// 70% opacity

	// History Size

	historySize = -1;	// Infinite

	// Tabs
	useTabBar = false;		// TEMP
}

void BaulkTerm::configurationLoad() {
	QVariant tmp;

	opacity = ( tmp = xmlConfig->option("terminalOpacity") ) == QVariant("") ? opacity
		: tmp.toDouble();

	font.fromString( ( tmp = xmlConfig->option("terminalFont") ) == QVariant("") ? font.toString()
		: tmp.toString() );

	historySize = ( tmp = xmlConfig->option("terminalHistorySize") ) == QVariant("") ? historySize
		: tmp.toInt();

	configurationSave();
}

void BaulkTerm::configurationSave() {
	xmlConfig->setOption( "terminalOpacity", QVariant( opacity ) );
	xmlConfig->setOption( "terminalFont", QVariant( font ) );
	xmlConfig->setOption( "terminalHistorySize", QVariant( historySize ) );

	// Save Config to File
	xmlConfig->saveConfig();
}

void BaulkTerm::configurationSet() {
	term->setHistorySize( historySize );
	term->setTerminalFont( font );
	term->setOpacity( opacity );
}

// Reimplemented Functions ************************************************************************
void BaulkTerm::resizeEvent( QResizeEvent *event ) {
	term->updateImage();
}

// Tabs *******************************************************************************************
void BaulkTerm::newTab() {
	term = new QTermWidget( startPriority, this );

	// Use Current Configuration Options on new terminal
	configurationSet();

	// Add terminal to tabbed view
	tabLayer->addWidget( term );
	tabBar->addTab( QString("Terminal %1").arg( tabLayer->count() ) );

	term->updateImage();
}

void BaulkTerm::closeTab() {
	// Remove terminal from tabs
	tabBar->removeTab( tabLayer->currentIndex() );
	tabLayer->removeWidget( term );

	// Close Terminal if there are no more tabs
	if ( tabLayer->count() < 1 )
		close();
}

