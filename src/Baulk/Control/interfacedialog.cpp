// Baulk - Interface Dialog - Baulk Control
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	interfacedialog.cpp
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
#include "interfacedialog.h"

// Constructors ***********************************************************************************
BaulkInterfaceDialog::BaulkInterfaceDialog( BaulkWidget *parent ) : QObject( parent ) {
	parentWidget = parent;
}

// Dialogs ****************************************************************************************
void BaulkInterfaceDialog::newWidgetDialogLoader() {
	newWidgetDialog = new BaulkDialog( parentWidget );

	// Window Title
	newWidgetDialog->setWindowTitle( tr("New Widget") );

	// Layout
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins( 0,0,0,0 );
	newWidgetDialog->setLayout( layout );

	// Title
	QLabel *title = new QLabel( tr("<big><b>Select a widget to create:</b></big>") );
	title->setMargin( 5 );
	layout->addWidget( title );

	// ListView
	newListView = new QListView;
	newListViewModel = new QStringListModel( ( (BaulkControl*)parentWidget )->libraryList().name );
	newListView->setModel( newListViewModel );
	layout->addWidget( newListView );

	// Connections
	connect( newListView, SIGNAL( activated( QModelIndex ) ), this, SLOT( newWidgetAccepted( QModelIndex ) ) );
	connect( this, SIGNAL( newWidget( LibraryLoader* ) ), (BaulkControl*)parentWidget, SLOT( loadMainWidget( LibraryLoader* ) ) );

	// Show Dialog
	newWidgetDialog->show();
}

// (Interface)Signal->Slot->Signal(Controller) ****************************************************
void BaulkInterfaceDialog::newWidgetAccepted( QModelIndex index ) {
	emit newWidget( ( (BaulkControl*)parentWidget )->libraryList().library[index.row()] );
	newWidgetDialog->accept();
	disconnect( newListView, SIGNAL( activated( QModelIndex ) ), this, SLOT( newWidgetAccepted( QModelIndex ) ) );
	disconnect( this, SIGNAL( newWidget( LibraryLoader* ) ), (BaulkControl*)parentWidget, SLOT( loadMainWidget( LibraryLoader* ) ) );
}

