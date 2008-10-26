// Baulk - WebBaulk - DLL Wrapper
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	wrapper_webbaulk.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	DLL Wrapper for WebBaulk
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

#ifndef __WRAPPER_WEBBAULK_H
#define __WRAPPER_WEBBAULK_H

#ifdef Q_WS_WIN
	#define EXPORTDLL __declspec(dllexport)
#else
	#define EXPORTDLL
#endif


#include <QWidget>

#include <baulkwidget.h>

#include "webbaulk.h"

// Exported Symbols
extern "C" EXPORTDLL {
	QStringList symbolList();

	BaulkWidget *webbaulk_mainWidget( QWidget *parent );
}

// Misc Declarations
WebBaulk *browser;

#endif
