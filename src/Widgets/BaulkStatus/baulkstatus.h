// Baulk - Baulk Status - Information About the Current Window Instance of Baulk
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	baulkstatus.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	Provides information to the user on running information of Baulk Control 
//	and the window instance that houses it.
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

#ifndef __BAULKSTATUS_H
#define __BAULKSTATUS_H

#include <QTextBrowser>
#include <QVBoxLayout>

#include <baulkwidget.h>

class BaulkStatus : public BaulkWidget {
	Q_OBJECT

public:
	BaulkStatus( BaulkWidget *parent = 0 );

private:
	QTextBrowser *messageBrowser;

private slots:
	void updateMsgLog( QStringList msgLogs );
};

#endif

