// Baulk - Common Functions and Classes for WebBaulk
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

#ifndef __COMMON_H
#define __COMMON_H

#include <QToolButton>
#include <QTreeWidget>

// Common Functions and Classes for WebBaulk

//! ToolButton Convenience class
class ToolButton : public QToolButton {
	Q_OBJECT

public:
	//! Constructor allowing for text to be added directly
	ToolButton( QString text, QWidget *parent = 0 );
};

#endif

