// Baulk - Baulk Window
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
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

#ifndef __BAULKWINDOW_H
#define __BAULKWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QWidget>

//! Baulk reimplementation of QMainWindow
/*!
 * A QMainWindow reimplementation useful for adding features to all of Baulk
 */
class BaulkWindow : public QMainWindow {
	Q_OBJECT

public:
	BaulkWindow( bool allowDirectUserClose = true, QWidget *parent = 0 );
	~BaulkWindow();

public slots:
	void forceClose();

	void updateWindowTitle( QString title );

protected:
	virtual void closeEvent( QCloseEvent *event );

signals:
	void userAttemptedClose();

};

#endif

