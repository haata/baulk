// Baulk - WebBaulk - Web Browser for Baulk
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

#include "webbaulk.h"

// Constructor ************************************************************************************
WebBaulk::WebBaulk( QWidget *parent ) : BaulkWidget( parent ) {
	mainLayout = new QVBoxLayout;
	mainLayout->setContentsMargins( 0,0,0,0 );
	setLayout( mainLayout );

	subLayout = new QSplitter( Qt::Horizontal );
	subLayout->setContentsMargins( 0,0,0,0 );
	subLayout->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
	mainLayout->addWidget( subLayout );
	
	// Tab Layer
	tabLayer = new QStackedWidget;
	tabLayer->setContentsMargins( 0,0,0,0 );
	subLayout->addWidget( tabLayer );

	// Initial Web View
	newTab();
	setFocusProxy( webview ); // Perhaps not needed
	
	// Convenience Widgets
	topBarSetup();

	// Information Viewer
	infoViewerSetup();

	// Initial Focus
	addressBarLineEdit->setFocus();
}

// Tabs *******************************************************************************************
void WebBaulk::newTab() {
	int newIndex = 0;
	if ( tabLayer->count() > 0 )
		newIndex = tabLayer->currentIndex() + 1;

	webview = new QWebView( this );
	webview->load( QUrl("http://google.ca") );
	tabLayer->insertWidget( newIndex, webview );

	// Set View
	tabLayer->setCurrentIndex( newIndex );

	// Add to InfoViewer
	if ( tabTree != 0 ) {
		connect( webview, SIGNAL( titleChanged( QString ) ), this, SLOT( updateTabTitle( QString ) ) );
	}
}

void WebBaulk::nextTab() {
	int count = tabLayer->count();
	int newIndex = tabLayer->currentIndex() + 1;

	if ( newIndex >= count )
		newIndex = 0;

	tabLayer->setCurrentIndex( newIndex );
}

void WebBaulk::prevTab() {
	int count = tabLayer->count();
	int newIndex = tabLayer->currentIndex() - 1;

	if ( newIndex < 0 )
		newIndex = count - 1;

	tabLayer->setCurrentIndex( newIndex );
}

// Top Bar ****************************************************************************************
void WebBaulk::topBarSetup() {
	// Widgets
	loadLabel = new QLabel;
	addressBarLineEdit = new QLineEdit;
	nextToolButton = new ToolButton( tr("P ->") );
	backToolButton = new ToolButton( tr("<- P") );
	refreshToolButton = new ToolButton( tr("O") );
	stopToolButton = new ToolButton( tr("X") );

	newTabToolButton = new ToolButton( tr("NT") );
	nextTabToolButton = new ToolButton( tr("T ->") );
	previousTabToolButton = new ToolButton( tr("<- T") );
	
	// Connections
	connect( backToolButton, SIGNAL( clicked() ), webview, SLOT( back() ) );
	connect( nextToolButton, SIGNAL( clicked() ), webview, SLOT( forward() ) );
	connect( refreshToolButton, SIGNAL( clicked() ), webview, SLOT( reload() ) );
	connect( stopToolButton, SIGNAL( clicked() ), webview, SLOT( stop() ) );

	connect( newTabToolButton, SIGNAL( clicked() ), this, SLOT( newTab() ) );
	connect( nextTabToolButton, SIGNAL( clicked() ), this, SLOT( nextTab() ) );
	connect( previousTabToolButton, SIGNAL( clicked() ), this, SLOT( prevTab() ) );

	connect( addressBarLineEdit, SIGNAL( returnPressed() ), this, SLOT( acceptUrl() ) );
	connect( webview, SIGNAL( urlChanged( QUrl ) ), this, SLOT( updateUrl( QUrl ) ) );
	connect( webview, SIGNAL( loadProgress( int ) ), this, SLOT( statusUpdate( int ) ) );

	// Top Layout
	QHBoxLayout *topWidgetBar = new QHBoxLayout;
	topWidgetBar->setSpacing( 1 );
	topWidgetBar->setContentsMargins( 0,0,0,0 );

	// Layout
	topWidgetBar->addWidget( backToolButton );
	topWidgetBar->addWidget( nextToolButton );
	topWidgetBar->addWidget( refreshToolButton );
	topWidgetBar->addWidget( stopToolButton );
	topWidgetBar->addWidget( addressBarLineEdit );
	topWidgetBar->addWidget( previousTabToolButton );
	topWidgetBar->addWidget( newTabToolButton );
	topWidgetBar->addWidget( nextTabToolButton );
	topWidgetBar->addWidget( loadLabel );

	mainLayout->insertLayout( 0, topWidgetBar );
}

// Status *****************************************************************************************
void WebBaulk::statusUpdate( int progress ) {
	loadLabel->setText( QString("%1\%").arg( progress) );
}

// Information Viewer *****************************************************************************
void WebBaulk::infoViewerSetup() {
	infoLayer = new QStackedWidget;
	subLayout->insertWidget( 0, infoLayer );

	tabTree = new QTreeWidget;
	tabTree->setColumnCount( 1 );

	for ( int c = 0; c < tabLayer->count(); ++c ) {
		QTreeWidgetItem *tab = new QTreeWidgetItem();
		QWebView *curWebView = (QWebView*)( tabLayer->widget( c ) );
		tab->setText( 0, curWebView->title() );
		tabTree->addTopLevelItem( tab );
		connect( curWebView, SIGNAL( titleChanged( QString ) ), this, SLOT( updateTabTitle( QString ) ) );
	}

	infoLayer->addWidget( tabTree );
}

// URL ********************************************************************************************
void WebBaulk::acceptUrl() {
	QString inputString = addressBarLineEdit->text();

	// Remove Whitespace
	inputString = inputString.remove(" ");

	// Create Url
	QUrl input = QUrl( inputString );

	// Use http by default
	if ( input.scheme() == "" ) {
		input.setUrl( QString("http://%1").arg( inputString ) );
		qDebug( QString("Loading %1").arg( input.toString() ).toUtf8() );
	}

	// Load Url
	webview->load( input );
}

void WebBaulk::updateUrl( QUrl url ) {
	addressBarLineEdit->setText( url.toString() );
}

// Title ******************************************************************************************
void WebBaulk::updateTabTitle( QString title ) {
	for ( int c = 0; c < tabLayer->count(); ++c ) {
	//	if ( ( (QWebView*) tabLayer->widget( c ) )->title() = title )
	}
}

