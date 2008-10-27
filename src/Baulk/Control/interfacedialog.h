// Baulk - Interface Dialog - Baulk Control
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	interfacedialog.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	The GUI Controller for all control options in Baulk.
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

#include <QObject>
#include <QWidget>

#include <baulkdialog.h>
#include <baulkwidget.h>

class BaulkInterfaceDialog : public QObject {
	Q_OBJECT

public:
	BaulkInterfaceDialog( BaulkWidget *parent );

public slots:
	void newWidgetDialog();

private:
	BaulkWidget *parentWidget;
};

#endif

