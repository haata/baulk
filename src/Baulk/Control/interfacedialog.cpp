// Baulk - Interface Dialog - Baulk Control
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
	actionsTableView = new QTableWidget( list.count() + 1, 3 );
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

	// Add Close Item
	actionsTableView->setItem( list.count(), 0, new QTableWidgetItem( tr("Close Menu") ) );
	actionsTableView->setItem( list.count(), 1, new QTableWidgetItem( tr("N/A") ) );
	actionsTableView->setItem( list.count(), 2, new QTableWidgetItem( "Close" ) );

	actionsTableView->setShowGrid( false );		// Hide Grid
	actionsTableView->setWordWrap( true );		// Allow Word Wrap
	actionsTableView->verticalHeader()->hide();	// Hide Vertical Headers
	actionsTableView->horizontalHeader()->hide();	// Hide Horizontal Headers
	actionsTableView->resizeColumnToContents( 1 );	// Resize Hotkey Column to optimal size
	actionsTableView->setColumnWidth( 0,		// TODO Make resizing dynamic 
		220 - actionsTableView->columnWidth( 1 ) );
	actionsTableView->resizeRowsToContents();	// Resize Rows to allow for word wrap
	layout->addWidget( actionsTableView );

	// Connections
	connect( actionsTableView, SIGNAL( itemDoubleClicked( QTableWidgetItem* ) ), 
		this, SLOT( actionsDialogHotkeyEdit( QTableWidgetItem* ) ) );
	connect( actionsTableView, SIGNAL( cellActivated( int, int ) ), 
		this, SLOT( actionsDialogHotkeyAccepted( int, int ) ) );
	connect( actionsTableView, SIGNAL( cellChanged( int, int ) ),
		this, SLOT( actionsDialogHotkeyModified( int, int ) ) );

	// Show Dialog
	actionsDialog->show();
}

// ** Configuration Dialog
void BaulkInterfaceDialog::configurationDialogLoader() {
	configurationDialog = new BaulkDialog( parentWidget );

	BaulkControl *control = (BaulkControl*)parentWidget;

	// Window Title
	configurationDialog->setWindowTitle( tr("Widget Configuration") );

	// Layout
	QVBoxLayout *vlayout = new QVBoxLayout;
	vlayout->setContentsMargins( 0,0,0,0 );

	QHBoxLayout *hlayout = new QHBoxLayout;
	hlayout->setContentsMargins( 0,0,0,0 );
	hlayout->addLayout( vlayout );
	configurationDialog->setLayout( hlayout );

	// Widget Tree
	configurationTree = new QTreeWidget;
	hlayout->insertWidget( 0, configurationTree );

	// Title
	QLabel *title = new QLabel( tr("<big><b>Configs:</b></big>") );
	title->setWordWrap( true );
	title->setMargin( 5 );
	vlayout->addWidget( title );

	// Show Dialog
	configurationDialog->show();
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
	QStringList list = control->libraryList().name;
	list << tr("Close Menu");
	newListViewModel = new QStringListModel( list );
	newListView->setModel( newListViewModel );
	layout->addWidget( newListView );

	// Show Dialog
	newWidgetDialog->show();

	// Connections
	connect( newListView, SIGNAL( activated( QModelIndex ) ), 
		this, SLOT( newWidgetAccepted( QModelIndex ) ) );
	connect( this, SIGNAL( newWidget( LibraryLoader* ) ), 
		control, SLOT( loadMainWidget( LibraryLoader* ) ) );
}

// (Interface)Signal->Slot->Signal(Controller) ****************************************************
// ** Hotkeys
void BaulkInterfaceDialog::actionsDialogHotkeyAccepted( int row, int column ) {
	// Impossible Case (at least should be)
	if ( column == 2 ) {
		qCritical( tr("%1\n\tBUG - You selected a hidden column").arg( errorName() ).toUtf8() );
		return;
	}

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
		QString index = actionsTableView->item( row, 2 )->text();
		if ( index != "Close" )
			list[index.toInt()]->trigger();
	}
}

// ** Hotkey Modified
void BaulkInterfaceDialog::actionsDialogHotkeyModified( int row, int column ) {
	if ( column != 1 ) {
		qCritical( tr("%1\n\tBUG - You should only be editing the Hotkey column").arg( errorName() ).toUtf8() );
		return;
	}

	BaulkControl *control = (BaulkControl*)parentWidget;

	// Modify Shortcut
	control->modifyGlobalKeyShortcut( actionsTableView->item( row, 2 )->text().toInt(), actionsTableView->item( row, 1 )->text() );
}

// ** New Widget
void BaulkInterfaceDialog::newWidgetAccepted( QModelIndex index ) {
	BaulkControl *control = (BaulkControl*)parentWidget;

	// Close the dialog
	newWidgetDialog->accept();

	// Do not emit a signal if the index is outside the bounds of the list
	if( index.row() < control->libraryList().name.count() )
		emit newWidget( control->libraryList().library[index.row()] );

	// Disconnects, so the slots are not call again on the next widget select
	disconnect( newListView, SIGNAL( activated( QModelIndex ) ), 
		this, SLOT( newWidgetAccepted( QModelIndex ) ) );
	disconnect( this, SIGNAL( newWidget( LibraryLoader* ) ), 
		control, SLOT( loadMainWidget( LibraryLoader* ) ) );
}

// Dialog Functionality Slots *********************************************************************
// ** Edit Hotkey
void BaulkInterfaceDialog::actionsDialogHotkeyEdit( QTableWidgetItem *item ) {
	// Only edit the item if it is a hotkey and if it is not the Close Item
	if ( item->column() == 1 && actionsTableView->item( item->row(), 2 )->text() != "Close" )
		actionsTableView->editItem( item );
}

