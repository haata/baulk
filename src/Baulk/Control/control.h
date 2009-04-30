// Baulk - Control
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

#ifndef __CONTROL_H
#define __CONTROL_H

#include <QAction>
#include <QApplication>
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

//! The main control for Baulk. 
/**
 * Handles most, if not all user interaction for Baulk, minus, what is
 *  provided by each Widget.
 */
class BaulkControl : public BaulkWidget {
	Q_OBJECT

public:
	//! Default Constructor
	BaulkControl( QWidget *parent = 0 );

	//! Struct for list of libraries, contains a QStringList of names and QList of library loaders
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
	//! Main Layouts
	QHBoxLayout *topHLayout;
	QVBoxLayout *topVLayout;

	//! Tab Layer
	QStackedWidget *tabLayer;

	//! Dynamic Layout
	QSplitter *dynTopLayout;
	QSplitter *dynBotLayout;
	int lastKnownGoodIndex;
	bool invertIndex;

	//! Global QActions
	QList<QAction*> glbQActions;

	//! Interface Dialog
	BaulkInterfaceDialog *interfaceDialog;

	//! Library List
	LibraryList libList;

	//! Baulk Config Loader/Saver
	BaulkXML *xmlConfig;


	//! QAction Setup
	QAction *addGlobalAction( QString title, QString keyShortcut, bool globalConnect = false );
	void setupQActions();

	//! Application Name for Errors
	QString errorName() const { return tr("BaulkControl"); }

	//! Widget Finders
	int dynBotIndex();
	int dynTopIndex();

private slots:
	//! Dynamic Librariess
	void loadLibraries();

	//! Instanciates Information Client
	void startInformationClient();

	//! Tile Manipulation ** Focus
	void focusDec();
	void focusDecBorder();
	void focusDown();
	void focusInc();
	void focusIncBorder();
	void focusLeft();
	void focusLayoutDec();
	void focusLayoutInc();
	void focusRight();
	void focusUp();
	//! Tile Manipulation ** Moving
	void moveDec();
	void moveDecBorder();
	void moveDown();
	void moveInc();
	void moveIncBorder();
	void moveLeft();
	void moveLayoutDec();
	void moveLayoutInc();
	void moveRight();
	void moveUp();
	//! Tile Manipulation ** Orientation
	void swapOrientationBot();
	void swapOrientationTop();
	//! Tile Manipulation ** Removal
	void removeWidget();

	//! Assistive Function
	void globalActionTriggered();

protected:
	virtual void closeEvent( QCloseEvent *event );
	
};

#endif

