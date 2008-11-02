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
// ** Actions Dialog
void BaulkInterfaceDialog::actionsDialogLoader() {
	actionsDialog = new BaulkDialog( parentWidget );

	BaulkControl *control = (BaulkControl*)parentWidget;

	// Window Title
	actionsDialog->setWindowTitle( tr("Available Actions") );

	// Layout
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins( 0,0,0,0 );
	actionsDialog->setLayout( layout );

	// Title
	QLabel *title = new QLabel( tr("<big><b>Select an action to use or edit:</b></big>") );
	title->setWordWrap( true );
	title->setMargin( 5 );
	layout->addWidget( title );

	// TableView
	QList<QAction*> list = control->globalQActions();
	actionsTableView = new QTableWidget( list.count(), 3 );
	actionsTableView->setEditTriggers( QAbstractItemView::NoEditTriggers );
	for ( int row = 0; row < list.count(); ++row ) {
		// Hotkey Name
		actionsTableView->setItem( row, 0, new QTableWidgetItem( list[row]->text() ) );
		// Hotkey
		actionsTableView->setItem( row, 1, new QTableWidgetItem( list[row]->shortcut().toString() ) );
		// List Key, Hidden from view
		actionsTableView->setItem( row, 2, new QTableWidgetItem( QString("%1").arg( row ) ) );
	}
	actionsTableView->hideColumn( 2 ); 		// Hide Key Column
	actionsTableView->sortItems( 0 );		// Sort Items by the first Column
	actionsTableView->setShowGrid( false );		// Hide Grid
	actionsTableView->setWordWrap( true );		// Allow Word Wrap
	actionsTableView->verticalHeader()->hide();	// Hide Vertical Headers
	actionsTableView->horizontalHeader()->hide();	// Hide Horizontal Headers
	actionsTableView->resizeColumnToContents( 1 );	// Resize Hotkey Column to optimal size
	actionsTableView->resizeRowsToContents();	// Resize Rows to allow for word wrap
	layout->addWidget( actionsTableView );

	// Connections
	connect( actionsTableView, SIGNAL( itemDoubleClicked( QTableWidgetItem* ) ), 
		this, SLOT( actionsDialogHotkeyEdit( QTableWidgetItem* ) ) );
	connect( actionsTableView, SIGNAL( cellActivated( int, int ) ), 
		this, SLOT( actionsDialogHotkeyAccepted( int, int ) ) );

	// Show Dialog
	actionsDialog->show();
}

// ** New Widget Dialog
void BaulkInterfaceDialog::newWidgetDialogLoader() {
	newWidgetDialog = new BaulkDialog( parentWidget );

	BaulkControl *control = (BaulkControl*)parentWidget;

	// Window Title
	newWidgetDialog->setWindowTitle( tr("New Widget") );

	// Layout
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins( 0,0,0,0 );
	newWidgetDialog->setLayout( layout );

	// Title
	QLabel *title = new QLabel( tr("<big><b>Select a widget to create:</b></big>") );
	title->setWordWrap( true );
	title->setMargin( 5 );
	layout->addWidget( title );

	// ListView
	newListView = new QListView;
	newListView->setEditTriggers( QAbstractItemView::NoEditTriggers );
	newListViewModel = new QStringListModel( control->libraryList().name );
	newListView->setModel( newListViewModel );
	layout->addWidget( newListView );

	// Connections
	connect( newListView, SIGNAL( activated( QModelIndex ) ), 
		this, SLOT( newWidgetAccepted( QModelIndex ) ) );
	connect( this, SIGNAL( newWidget( LibraryLoader* ) ), 
		control, SLOT( loadMainWidget( LibraryLoader* ) ) );

	// Show Dialog
	newWidgetDialog->show();
}

// (Interface)Signal->Slot->Signal(Controller) ****************************************************
// ** Hotkeys
void BaulkInterfaceDialog::actionsDialogHotkeyAccepted( int row, int column ) {
	// Impossible Case (at least should be)
	if ( column == 2 )
		qCritical( tr("%1\n\tBUG - You selected a hidden column").arg( errorName() ).toUtf8() );

	// Hotkey Edit
	if ( column == 1 )
		actionsDialogHotkeyEdit( actionsTableView->item( row, column ) );
	// Hotkey Activation
	else {
		BaulkControl *control = (BaulkControl*)parentWidget;
		QList<QAction*> list = control->globalQActions();

		// Close the dialog
		actionsDialog->accept();

		// Disconnect Slots
		disconnect( actionsTableView, SIGNAL( itemDoubleClicked( QTableWidgetItem* ) ), 
			this, SLOT( actionsDialogHotkeyEdit( QTableWidgetItem* ) ) );
		disconnect( actionsTableView, SIGNAL( cellActivated( int, int ) ), 
			this, SLOT( actionsDialogHotkeyAccepted( int, int ) ) );

		// Activate Hotkey
		list[actionsTableView->item( row, 2 )->text().toInt()]->trigger();
	}
}

// ** New Widget
void BaulkInterfaceDialog::newWidgetAccepted( QModelIndex index ) {
	BaulkControl *control = (BaulkControl*)parentWidget;

	emit newWidget( control->libraryList().library[index.row()] );

	// Close the dialog
	newWidgetDialog->accept();

	// Disconnects, so the slots are not call again on the next widget select
	disconnect( newListView, SIGNAL( activated( QModelIndex ) ), 
		this, SLOT( newWidgetAccepted( QModelIndex ) ) );
	disconnect( this, SIGNAL( newWidget( LibraryLoader* ) ), 
		control, SLOT( loadMainWidget( LibraryLoader* ) ) );
}

// Dialog Functionality Slots *********************************************************************
// ** Edit Hotkey
void BaulkInterfaceDialog::actionsDialogHotkeyEdit( QTableWidgetItem *item ) {
	// Only edit the item if it is a hotkey
	if ( item->column() == 1 )
		actionsTableView->editItem( item );
}

