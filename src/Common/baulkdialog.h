// Baulk - Baulk Dialog
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

#ifndef __BAULKDIALOG_H
#define __BAULKDIALOG_H

#include <QCloseEvent>
#include <QDialog>
#include <QWidget>


//! Baulk reimplementation of QDialog
/*!
 * A common interface for dialogs in Baulk to be modified globally.
 */
class BaulkDialog : public QDialog {
	Q_OBJECT

public:
	BaulkDialog( bool userCancel = false, QWidget *parent = 0 );
	~BaulkDialog();

public slots:
	virtual void reject();

private:
	bool forceQuit;

protected:
	virtual void closeEvent( QCloseEvent *event );

signals:
	void closed();

};

#endif

