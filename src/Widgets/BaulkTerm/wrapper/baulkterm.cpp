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
	//tabBar = new QTabBar( this );
	//if ( !useTabBar )
		//tabBar->hide();

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

	//layout->addWidget( tabBar );

	layout->addWidget( tabLayer );

	// Widget Settings
	setFocusProxy( term );
	setLayout( layout );

	// Connections
	connect( term, SIGNAL( finished() ), this, SIGNAL( finished() ) );
	connect( term, SIGNAL( finished() ), this, SLOT( closeTab() ) );
	connect( term, SIGNAL( mouseSignal( int, int, int, int ) ), this, SLOT( rightClickMenu( int, int, int, int ) ) );
	connect( term, SIGNAL( rightClickAction() ), this, SLOT( rightClickAction() ) );
}

// Configuration **********************************************************************************
void BaulkTerm::configurationDefaults() {
	// Font
	font = QFont( "Terminus" );
	font.setPointSize( 12 );

	// Transparency
	opacity = 0.7;		// 70% opacity
	fadeOpacity = 0.5;	// 50% opacity

	// History Size

	historySize = -1;	// Infinite

	// Tabs
	useTabBar = false;		// TEMP

	// Normal Colours
	foreground	.setOptions( QColor(0xD3,0xD3,0xD3), 0, 0 );
	background	.setOptions( QColor(0x00,0x00,0x00), 1, 0 );
	black		.setOptions( QColor(0x67,0x67,0x67), 0, 0 );
	red		.setOptions( QColor(0xEA,0x68,0x68), 0, 0 );
	green		.setOptions( QColor(0xAB,0xCB,0x8D), 0, 0 );
	yellow		.setOptions( QColor(0xE8,0xAE,0x5B), 0, 0 );
	blue		.setOptions( QColor(0x71,0xC5,0xF4), 0, 0 );
	magenta		.setOptions( QColor(0xE2,0xBA,0xF1), 0, 0 );
	cyan		.setOptions( QColor(0x21,0xF1,0xEA), 0, 0 );
	white		.setOptions( QColor(0xD3,0xD3,0xD3), 0, 0 );

	// Intensive Colours
	intForeground	.setOptions( QColor(0x00,0x00,0x00), 0, 1 );
	intBackground	.setOptions( QColor(0xD3,0xD3,0xD3), 1, 0 );
	intBlack	.setOptions( QColor(0x75,0x75,0x75), 0, 0 );
	intRed		.setOptions( QColor(0xFF,0x72,0x72), 0, 0 );
	intGreen	.setOptions( QColor(0xAF,0xD7,0x8A), 0, 0 );
	intYellow	.setOptions( QColor(0xFF,0xA7,0x5D), 0, 0 );
	intBlue		.setOptions( QColor(0x67,0xCD,0xE9), 0, 0 );
	intMagenta	.setOptions( QColor(0xEC,0xAE,0xE9), 0, 0 );
	intCyan		.setOptions( QColor(0x36,0xFF,0xFC), 0, 0 );
	intWhite	.setOptions( QColor(0xFF,0xFF,0xFF), 0, 0 );
}

void BaulkTerm::configurationLoad() {
	QVariant tmp;

	opacity = ( tmp = xmlConfig->option("terminalOpacity") ) == QVariant("") ? opacity
		: tmp.toDouble();
	fadeOpacity = ( tmp = xmlConfig->option("terminalFadeOpacity") ) == QVariant("") ? fadeOpacity
		: tmp.toDouble();

	font.fromString( ( tmp = xmlConfig->option("terminalFont") ) == QVariant("") ? font.toString()
		: tmp.toString() );

	historySize = ( tmp = xmlConfig->option("terminalHistorySize") ) == QVariant("") ? historySize
		: tmp.toInt();

	// Normal Colours
	foreground.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "colour", QVariant("Foreground") ) ) == QVariant("")
		? foreground.toVariant() : tmp );
	background.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "colour", QVariant("Background") ) ) == QVariant("")
		? background.toVariant() : tmp );
	black.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "colour", QVariant("Black") ) ) == QVariant("")
		? black.toVariant() : tmp );
	red.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "colour", QVariant("Red") ) ) == QVariant("")
		? red.toVariant() : tmp );
	green.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "colour", QVariant("Green") ) ) == QVariant("")
		? green.toVariant() : tmp );
	yellow.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "colour", QVariant("Yellow") ) ) == QVariant("")
		? yellow.toVariant() : tmp );
	blue.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "colour", QVariant("Blue") ) ) == QVariant("")
		? blue.toVariant() : tmp );
	magenta.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "colour", QVariant("Magenta") ) ) == QVariant("")
		? magenta.toVariant() : tmp );
	cyan.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "colour", QVariant("Cyan") ) ) == QVariant("")
		? cyan.toVariant() : tmp );
	white.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "colour", QVariant("White") ) ) == QVariant("")
		? white.toVariant() : tmp );

	// Intensive Colours
	intForeground.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "intensiveColour", QVariant("Foreground") ) ) == QVariant("")
		? intForeground.toVariant() : tmp );
	intBackground.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "intensiveColour", QVariant("Background") ) ) == QVariant("")
		? intBackground.toVariant() : tmp );
	intBlack.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "intensiveColour", QVariant("Black") ) ) == QVariant("")
		? intBlack.toVariant() : tmp );
	intRed.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "intensiveColour", QVariant("Red") ) ) == QVariant("")
		? intRed.toVariant() : tmp );
	intGreen.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "intensiveColour", QVariant("Green") ) ) == QVariant("")
		? intGreen.toVariant() : tmp );
	intYellow.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "intensiveColour", QVariant("Yellow") ) ) == QVariant("")
		? intYellow.toVariant() : tmp );
	intBlue.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "intensiveColour", QVariant("Blue") ) ) == QVariant("")
		? intBlue.toVariant() : tmp );
	intMagenta.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "intensiveColour", QVariant("Magenta") ) ) == QVariant("")
		? intMagenta.toVariant() : tmp );
	intCyan.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "intensiveColour", QVariant("Cyan") ) ) == QVariant("")
		? intCyan.toVariant() : tmp );
	intWhite.setFromVariant( 
	( tmp = xmlConfig->option( "terminalColour", "intensiveColour", QVariant("White") ) ) == QVariant("")
		? intWhite.toVariant() : tmp );


	configurationSave();
}

void BaulkTerm::configurationSave() {
	xmlConfig->setOption( "terminalOpacity", QVariant( opacity ) );
	xmlConfig->setOption( "terminalFadeOpacity", QVariant( fadeOpacity ) );
	xmlConfig->setOption( "terminalFont", QVariant( font ) );
	xmlConfig->setOption( "terminalHistorySize", QVariant( historySize ) );

	// Normal Colours
	xmlConfig->setOption( "terminalColour", foreground.toVariant(),
		"colour", QVariant("Foreground") );
	xmlConfig->setOption( "terminalColour", background.toVariant(),
		"colour", QVariant("Background") );
	xmlConfig->setOption( "terminalColour", black.toVariant(),
		"colour", QVariant("Black") );
	xmlConfig->setOption( "terminalColour", red.toVariant(),
		"colour", QVariant("Red") );
	xmlConfig->setOption( "terminalColour", green.toVariant(),
		"colour", QVariant("Green") );
	xmlConfig->setOption( "terminalColour", yellow.toVariant(),
		"colour", QVariant("Yellow") );
	xmlConfig->setOption( "terminalColour", blue.toVariant(),
		"colour", QVariant("Blue") );
	xmlConfig->setOption( "terminalColour", magenta.toVariant(),
		"colour", QVariant("Magenta") );
	xmlConfig->setOption( "terminalColour", cyan.toVariant(),
		"colour", QVariant("Cyan") );
	xmlConfig->setOption( "terminalColour", white.toVariant(),
		"colour", QVariant("White") );

	// Intensive Colours
	xmlConfig->setOption( "terminalColour", intForeground.toVariant(), 
		"intensiveColour", QVariant("Foreground") );
	xmlConfig->setOption( "terminalColour", intBackground.toVariant(), 
		"intensiveColour", QVariant("Background") );
	xmlConfig->setOption( "terminalColour", intBlack.toVariant(),
		"intensiveColour", QVariant("Black") );
	xmlConfig->setOption( "terminalColour", intRed.toVariant(),
		"intensiveColour", QVariant("Red") );
	xmlConfig->setOption( "terminalColour", intGreen.toVariant(),
		"intensiveColour", QVariant("Green") );
	xmlConfig->setOption( "terminalColour", intYellow.toVariant(),
		"intensiveColour", QVariant("Yellow") );
	xmlConfig->setOption( "terminalColour", intBlue.toVariant(),
		"intensiveColour", QVariant("Blue") );
	xmlConfig->setOption( "terminalColour", intMagenta.toVariant(),
		"intensiveColour", QVariant("Magenta") );
	xmlConfig->setOption( "terminalColour", intCyan.toVariant(),
		"intensiveColour", QVariant("Cyan") );
	xmlConfig->setOption( "terminalColour", intWhite.toVariant(),
		"intensiveColour", QVariant("White") );

	// Save Config to File
	xmlConfig->saveConfig();
}

void BaulkTerm::configurationSet() {
	term->setHistorySize( historySize );
	term->setTerminalFont( font );
	term->setOpacity( opacity );

	// Normal Colours
	term->setColor( 0, foreground.colour(), 	foreground.transparency(), 	foreground.bold() );
	term->setColor( 1, background.colour(), 	background.transparency(), 	background.bold() );
	term->setColor( 2, black.colour(), 		black.transparency(), 		black.bold() );
	term->setColor( 3, red.colour(), 		red.transparency(), 		red.bold() );
	term->setColor( 4, green.colour(), 		green.transparency(), 		green.bold() );
	term->setColor( 5, yellow.colour(), 		yellow.transparency(), 		yellow.bold() );
	term->setColor( 6, blue.colour(), 		blue.transparency(), 		blue.bold() );
	term->setColor( 7, magenta.colour(), 		magenta.transparency(), 	magenta.bold() );
	term->setColor( 8, cyan.colour(), 		cyan.transparency(), 		cyan.bold() );
	term->setColor( 9, white.colour(), 		white.transparency(), 		white.bold() );

	// Intensive Colours
	term->setColor( 10, foreground.colour(), 	foreground.transparency(), 	foreground.bold() );
	term->setColor( 11, background.colour(), 	background.transparency(), 	background.bold() );
	term->setColor( 12, black.colour(), 		black.transparency(), 		black.bold() );
	term->setColor( 13, red.colour(), 		red.transparency(), 		red.bold() );
	term->setColor( 14, green.colour(), 		green.transparency(), 		green.bold() );
	term->setColor( 15, yellow.colour(), 		yellow.transparency(), 		yellow.bold() );
	term->setColor( 16, blue.colour(), 		blue.transparency(), 		blue.bold() );
	term->setColor( 17, magenta.colour(), 		magenta.transparency(), 	magenta.bold() );
	term->setColor( 18, cyan.colour(), 		cyan.transparency(), 		cyan.bold() );
	term->setColor( 19, white.colour(), 		white.transparency(), 		white.bold() );
}

// Configuration Menus ****************************************************************************
void BaulkTerm::rightClickMenu( int button, int column, int line, int eventType ) {
	// TODO Doesn't work
	qDebug( "Button %d", button );
	qDebug( "Column %d", column );
	qDebug( "Line   %d", line );
	qDebug( "eventType %d", eventType );
}

void BaulkTerm::rightClickAction() {
	qDebug("RIGHT");
}

// Tabs *******************************************************************************************
void BaulkTerm::newTab() {
	term = new QTermWidget( startPriority, this );

	// Use Current Configuration Options on new terminal
	configurationSet();

	// Add terminal to tabbed view
	tabLayer->addWidget( term );
	//tabBar->addTab( QString("Terminal %1").arg( tabLayer->count() ) );

	term->updateImage();
}

void BaulkTerm::closeTab() {
	// Remove terminal from tabs
	//tabBar->removeTab( tabLayer->currentIndex() );
	tabLayer->removeWidget( term );

	// Close Terminal if there are no more tabs
	if ( tabLayer->count() < 1 )
		close();
}

// Reimplemented Functions ************************************************************************
void BaulkTerm::changeEvent( QEvent *event ) {
	switch ( event->type() ) { 
	case QEvent::ActivationChange:
		// Terminal has focus - unfade
		if ( isActiveWindow() )
			term->setOpacity( opacity );
		// Terminal lost focus - fade
		else
			term->setOpacity( fadeOpacity );
		break;
	default:
		qDebug("Default - %d", event->type() );
		break;
	}
	event->accept();
}

bool BaulkTerm::processCommandArgs() {
	// Note: Options that are decyphered are removed from the arguments list
	bool runApp = true;
	QStringList args = qApp->arguments();

	// Help
	if ( args.contains( tr("--h" ) ) || args.contains( tr("--help") ) ) {
		QString out = tr(
		"BaulkTerm - A Konsole based Qt4 terminal emulator\n"
		"Note: Some options may not be implemented yet\n"
		"Usage:\n"
		"  baulkTerm [OPTION...]\n"
		"\n"
		"Usual Options:\n"
		"  --h, --help             Show help options (this list)\n"
		"  --v, --version          BaulkTerm version\n"
		"\n"
		"Application Options:\n"
		"  --columns               Set number of columns\n"
		"  --e, --execute          Execute command\n"
		"  --font <font family> <font size>\n"
		"                          Initial terminal font used\n"
		"  --rows                  Set number of rows\n"
		);
		std::cout << out.toUtf8().data();
		return false;
	}

	// Version
	if ( args.contains( tr("--v") ) || args.contains( tr("--version") ) ) {
		QString out = tr(
		"BaulkTerm Version 0.1.git(%1)\n"
		).arg( "TODO" );
		std::cout << out.toUtf8().data();
		return false;
	}

	// Columns and Rows
	if ( args.contains( tr("--columns") ) || args.contains( tr("--rows") ) ) {
		bool ok;
		int horizontal = 80;
		int vertical = 60;
		for ( int c = 0; c + 1 < args.count(); ++c ) {
			if ( args[c] == tr("--columns") ) {
				horizontal = args[c + 1].toInt( &ok );
				if ( ok ) {
					args.removeAt( c );
					args.removeAt( c );
					--c;
					if ( c + 1 >= args.count() )
						break;
				}
			}
			if ( args[c] == tr("--rows") ) {
				vertical = args[c + 1].toInt( &ok );
				if ( ok ) {
					args.removeAt( c );
					args.removeAt( c );
					--c;
					if ( c + 1 >= args.count() )
						break;
				}
			}
		}

		term->setSize( horizontal, vertical );
	}

	// Execute Command (assumed last command decyphered)
	if ( args.contains( tr("--e") ) || args.contains( tr("--execute") ) ) {
		QString command;

		int count = 2;
		while ( count < args.count() ) {
			command += args[count] + " ";
			args.removeAt( count );
		}

		args.removeAt( 1 );

		qDebug( tr("Executing - %1").arg( command ).toUtf8() );
		command += "\n";
		term->sendText( command );
	}

	if ( args.count() > 1 ) {
		qFatal( tr("Invalid Command-Line Argument(s) - %1").arg( args.count() - 1 ).toUtf8() );
		return false;
	}

	return runApp;
}

void BaulkTerm::resizeEvent( QResizeEvent *event ) {
	term->updateImage();
	event->accept();
}

