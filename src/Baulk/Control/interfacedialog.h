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

#ifndef __INTERFACEDIALOG_H
#define __INTERFACEDIALOG_H

#include <QLabel>
#include <QListView>
#include <QModelIndex>
#include <QObject>
#include <QPushButton>
#include <QStringListModel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVariant>
#include <QVBoxLayout>
#include <QWidget>

#include <baulkdialog.h>
#include <baulkwidget.h>
#include <libraryloader.h>

/**
 * @author Jacob Alexander (HaaTa)
 *
 * The GUI Controller for all control options in Baulk.
 */
class BaulkInterfaceDialog : public QObject {
	Q_OBJECT

public:
	BaulkInterfaceDialog( BaulkWidget *parent );

public slots:
	// Control -> Dialog Connectors
	void actionsDialogLoader();
	void newWidgetDialogLoader();

private:
	// Dialogs
	BaulkDialog *actionsDialog;
	BaulkDialog *newWidgetDialog;

	// Controller
	BaulkWidget *parentWidget;

	// New Widget List
	QListView *newListView;
	QStringListModel *newListViewModel;

	// Hotkey List
	QTableWidget *actionsTableView;


	// Application Name for Errors
	QString errorName() const { return tr("BaulkInterfaceDialog"); }

private slots:
	// Dialog -> Control Connectors
	void actionsDialogHotkeyAccepted( int row, int column );
	void actionsDialogHotkeyModified( int row, int column );
	void newWidgetAccepted( QModelIndex index );

	// Dialog Functionality
	void actionsDialogHotkeyEdit( QTableWidgetItem *item );

signals:
	// Dialog -> Control Signals
	void newWidget( LibraryLoader *library );
};

#endif

