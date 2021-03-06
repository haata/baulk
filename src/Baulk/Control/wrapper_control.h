// Baulk - Control - DLL Wrapper
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	wrapper_control.h
//  Author(s):	Jacob Alexander (HaaTa)
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

#ifndef __WRAPPER_CONTROL_H
#define __WRAPPER_CONTROL_H

#ifdef Q_WS_WIN
	#define EXPORTDLL __declspec(dllexport)
#else
	#define EXPORTDLL
#endif


#include <QWidget>
#include <QMessageBox>

#include <baulkwidget.h>

#include "control.h"

//! DLL Wrapper for BaulkControl
// Exported Symbols *******************************************************************************
//! C Exported Symbols
extern "C" EXPORTDLL {
	//! List of available symbols
	QStringList symbolList();

	//! Main Widget
	BaulkWidget *control_mainWidget( QWidget *parent = 0 );

	//! Widget Name
	QString control_widgetName();

	//! Quit Event
	bool allowQuit();
}

// Misc Declarations ******************************************************************************
BaulkControl *control;

#endif

