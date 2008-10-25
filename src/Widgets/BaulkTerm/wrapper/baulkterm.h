// Baulk - qtermwidget Reimplement - BaulkTerm
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	baulkterm.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	Additional functionality for qtermwidget
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

#ifndef __BAULKTERM_H
#define __BAULKTERM_H

#include <QResizeEvent>
#include <QWidget>

#include <qtermwidget.h>

class BaulkTerm : public QTermWidget {
	Q_OBJECT

public:
	BaulkTerm( int startNow = 1, QWidget *parent = 0 );

protected:
	virtual void resizeEvent( QResizeEvent *event );
};

#endif

