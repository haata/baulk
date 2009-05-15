// Baulk
//
// Baulk - Copyright (C) 2008-2009 - Jacob Alexander
//   <haata at users.sf.net>
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

#ifndef __BAULK_H
#define __BAULK_H

#include <QDesktopWidget>
#include <QCloseEvent>
//#include <QMainWindow>
#include <QObject>
#include <QProcess>
#include <QTest>
#include <QWidget>

#include <baulkwidget.h>
#include <libraryloader.h>

//! Main GUI Entrance class for Baulk.
/*!
 * Handles:
 * - Loading BaulkControl Shared Library
 * - Connecting message output to BaulkControl
 * - Connecting the Window Titling setting to BaulkControl.
 */
class Baulk : public QObject {
	Q_OBJECT

public:
	//! Baulk Constructor
	Baulk( QWidget *parent = 0 );

	/*!
	 * This public function allows \link handler() \endlink
	 * to pass Console Out Messages into Baulk 
	 */
	bool updateMsgLogs( QStringList msgLogs );

	bool processCommandArgs();

private:
	//! BaulkControl Pointer
	BaulkWidget *controller;

	//! BaulkControl Library Pointer
	LibraryLoader *library;

private slots:
	//! Allows BaulkControl to change the Window Title
	void setWindowTitleName( QString windowTitle );

protected:
	/*! 
	 * Reimplemented QWidget Event that handles the application
	 * Quit Event
	 */ 
	virtual void closeEvent( QCloseEvent *event );
};

#endif

