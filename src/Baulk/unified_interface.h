// Baulk - Unified Interface
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

#ifndef __UNIFIED_INTERFACE_H
#define __UNIFIED_INTERFACE_H

#include "X11/xcb_windowmanipulation.h"

class UnifiedInterface : public XCBWindowManipulation {
	Q_OBJECT
public:
	UnifiedInterface( QObject *parent = 0 );
	~UnifiedInterface();
};

#endif

