// Baulk - Common - Baulk Widget
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

#ifndef __BAULKWIDGET_H
#define __BAULKWIDGET_H

#include <iostream>

#include <QApplication>
#include <QResizeEvent>
#include <QVariant>
#include <QVBoxLayout>
#include <QWidget>

#include "builddefines.h"

//! QWidget Reimplementation for Baulk
/*!
 *  A QWidget Reimplementation useful for adding subfeatures to all widgets in Baulk.
 */
class BaulkWidget : public QWidget {
	Q_OBJECT

public:
	//! Default Constructor
	BaulkWidget( QWidget *parent = 0 );
	//! Constructor for using a QWidget (or derivative) as BaulkWidget
	BaulkWidget( QWidget *wrapWidget, QWidget *parent );

	//! Internal message logs
	QStringList msgLogs() const;
	//! Add to internal message logs
	void setMsgLogs( QStringList msgLogs );


	//! BaulkServ Listen Name
	QString serverListenName() const;
	void setServerListenName( QString listenName );

	QString windowTitleName() const;
	void setWindowTitleName( QString titleName );

	//! Command Line Argument Processing
	virtual bool processCommandArgs();

public slots:

private:
	void widgetSetup();

protected:
	virtual void resizeEvent( QResizeEvent *event );

signals:
	void msgLogsUpdated( QStringList msgLogs );
	void serverListenNameSet( QString listenName );
	void windowTitleNameSet( QString titleName );
};

#endif

