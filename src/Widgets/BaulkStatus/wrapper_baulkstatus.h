// Baulk - Baulk Status - DLL Wrapper
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

#ifndef __WRAPPER_BAULKSTATUS_H
#define __WRAPPER_BAULKSTATUS_H

#ifdef Q_WS_WIN
	#define EXPORTDLL __declspec(dllexport)
#else
	#define EXPORTDLL
#endif


#include <QWidget>

#include <baulkwidget.h>

#include "baulkstatus.h"

// Exported Symbols *******************************************************************************
//! DLL Wrapper for Baulk Status
extern "C" EXPORTDLL {
	QStringList symbolList();

	BaulkWidget *baulkstatus_configWidget( QWidget *parent );
	BaulkWidget *baulkstatus_mainWidget( BaulkWidget *parent );

	QString baulkstatus_widgetName();
}

// Misc Declarations ******************************************************************************
BaulkStatus *status;

#endif

