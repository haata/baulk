// Baulk - Control
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	control.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	The main control for Baulk. Handles most, if not
//	all user interaction for Baulk, minus, what is
//	provided by each Widget.
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

#ifndef __CONTROL_H
#define __CONTROL_H

#include <QAction>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QRegExp>
#include <QSplitter>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>

#include <baulkwidget.h>
#include <baulkxml.h>
#include <client.h>
#include <libraryloader.h>

#include "interfacedialog.h"

class BaulkControl : public BaulkWidget {
	Q_OBJECT

public:
	BaulkControl( QWidget *parent = 0 );

	struct LibraryList {
		QStringList name;
		QList<LibraryLoader*> library;
	};

	LibraryList libraryList() const { return libList; }

	QList<QAction*> globalQActions() const { return glbQActions; }

public slots:
	void loadMainWidget( LibraryLoader *library );
	void modifyGlobalKeyShortcut( int key, QString keyShortcut );

private:
	// Main Layout
	QHBoxLayout *topHLayout;
	QVBoxLayout *topVLayout;

	// Tab Layer
	QStackedWidget *tabLayer;

	// Dynamic Layout
	QSplitter *dynTopLayout;
	QSplitter *dynBotLayout;

	// Global QActions
	QList<QAction*> glbQActions;

	// Interface Dialog
	BaulkInterfaceDialog *interfaceDialog;

	// Library List
	LibraryList libList;

	// Baulk Config Loader/Saver
	BaulkXML *xmlConfig;


	// QAction Setup
	QAction *addGlobalAction( QString title, QString keyShortcut );
	void setupQActions();

	// Application Name for Errors
	QString errorName() const { return tr("BaulkControl"); }

private slots:
	// Dynamic Librariess
	void loadLibraries();

	void startInformationClient();

	// Tile Manipulation
	void focusDown();
	void focusLeft();
	void focusRight();
	void focusUp();
	void swapOrientationBot();
	void swapOrientationTop();

protected:
	virtual void closeEvent( QCloseEvent *event );
	
};

#endif

