// Baulk - Baulk Dialog
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	baulkdialog.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	Baulk reimplementation of QDialog
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

#include <QDialog>
#include <QWidget>

class BaulkDialog : public QDialog {
	Q_OBJECT

public:
	BaulkDialog( QWidget *parent = 0 );

};

#endif

