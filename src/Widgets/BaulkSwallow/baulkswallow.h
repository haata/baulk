// Baulk - Baulk Swallow - Widget Embedder/Catcher for X11
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	baulkswallow.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	Allows the user to embed/swallow any X11 application as a Widget
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

#ifndef __BAULKSWALLOW_H
#define __BAULKSWALLOW_H

#include <baulkwidget.h>

class BaulkSwallow : public BaulkWidget {
	Q_OBJECT

public:
	BaulkSwallow( BaulkWidget *parent = 0 );
};

#endif

