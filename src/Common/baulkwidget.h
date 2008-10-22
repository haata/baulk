// Baulk - Common - Baulk Widget
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	baulkwidget.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	A QWidget, but a lot more useful.
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

#ifndef __BAULKWIDGET_H
#define __BAULKWIDGET_H

#include <QVariant>
#include <QVBoxLayout>
#include <QWidget>

class BaulkWidget : public QWidget {
	Q_OBJECT

public:
	BaulkWidget( QWidget *parent = 0 );
	// For using a QWidget (or derivative) as BaulkWidget
	BaulkWidget( QWidget *wrapWidget, QWidget *parent );

	// Properties
	QString serverListenName() const;
	void setServerListenName( QString listenName );

	QString windowTitleName() const;
	void setWindowTitleName( QString titleName );

public slots:

private:

signals:
	void serverListenNameSet( QString listenName );
	void windowTitleNameSet( QString titleName );
};

#endif

