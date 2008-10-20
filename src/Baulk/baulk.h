// Baulk
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	baulk.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	Loads first libraries, and decides whether to run in Server/Client
//	Mode (Multiple Windows) or Single App Mode.
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

#include <QCloseEvent>
#include <QMainWindow>
#include <QProcess>
#include <QTest>

#include <baulkwidget.h>
#include <libraryloader.h>

class Baulk : public QMainWindow {
	Q_OBJECT

public:
	Baulk( QWidget *parent = 0 );

private:
	BaulkWidget *controller;

protected:
	virtual void closeEvent( QCloseEvent *event );
};

#endif

