// Baulk - qtermwidget Reimplement - BaulkTerm
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

#ifndef __BAULKTERM_H
#define __BAULKTERM_H

#include <iostream>

#include <QEvent>
#include <QFont>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QTabBar>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include <baulkwidget.h>
#include <baulkxml.h>
#include <qtermwidget.h>

#include "terminalcolour.h"

/**
 * @author Jacob Alexander (HaaTa)
 *
 * Additional functionality for qtermwidget
 */
class BaulkTerm : public BaulkWidget {
	Q_OBJECT

public:
	BaulkTerm( int startNow = 1, QWidget *parent = 0 );


	// Command Line Args
	virtual bool processCommandArgs();

	// Start Terminal
	void startShellProgram();

private:
	int startPriority;

	QTermWidget *term;

	BaulkXML *xmlConfig;

	QTabBar *tabBar;
	QStackedWidget *tabLayer;

	QVBoxLayout *layout;

	// Configuration Settings
	qreal opacity;
	qreal fadeOpacity;

	int historySize;
	QString historyType;

	QFont font;

	bool useTabBar;

	QString shellProgram;

	// Normal Colours
	TerminalColour foreground;
	TerminalColour background;
	TerminalColour black;
	TerminalColour red;
	TerminalColour green;
	TerminalColour yellow;
	TerminalColour blue;
	TerminalColour magenta;
	TerminalColour cyan;
	TerminalColour white;

	// Intensive Colours
	TerminalColour intForeground;
	TerminalColour intBackground;
	TerminalColour intBlack;
	TerminalColour intRed;
	TerminalColour intGreen;
	TerminalColour intYellow;
	TerminalColour intBlue;
	TerminalColour intMagenta;
	TerminalColour intCyan;
	TerminalColour intWhite;


	// Configuration Functions
	void configurationDefaults();
	void configurationLoad();
	void configurationSave();
	void configurationSet();

private slots:
	void newTab();
	void closeTab();

	void xMouseInput( int, int, int, int );
	void rightClickAction();

	void updateWindowTitle();

protected:
	virtual void changeEvent( QEvent *event );
	virtual void resizeEvent( QResizeEvent *event );

signals:
	void finished();
};

#endif

