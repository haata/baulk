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

#include <QCloseEvent>
#include <QDialog>
#include <QEvent>
#include <QFont>
#include <QMainWindow>
#include <QResizeEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include <baulkwidget.h>
#include <baulkwindow.h>
#include <baulkxml.h>
#include <builddefines.h>
#include <qtermwidget.h>

#include "rightclickmenu.h"
#include "terminalcolour.h"

/**
 * @author Jacob Alexander (HaaTa)
 *
 * Additional functionality for qtermwidget
 */
class BaulkTerm : public BaulkWidget {
	Q_OBJECT

public:
	BaulkTerm( int startNow = 1, bool standalone = false, QWidget *parent = 0 );


	// Command Line Args
	virtual bool processCommandArgs();

	// Start Terminal
	void startShellProgram();

	// External Settings
	bool useDaemon() const { return daemonEnabled; }
	QString listenName() const { return daemonListenName; }

public slots:
	// New Terminal
	void newTerminal( bool useMainWindow = false );

private:
	int startPriority;

	// Terminal
	QTermWidget *term;
	QTermWidget *mainTerm;
	QList<QTermWidget*> termList;

	QVBoxLayout *termLayout;

	// Terminal Right Click Menu
	BaulkTermRightClickMenu *rightClickMenu;

	// Configuration File Pointer
	BaulkXML *xmlConfig;

	// Configuration Settings
	qreal opacity;
	qreal fadeOpacity;

	int windowHeight;
	int windowWidth;
	int windowXpos;
	int windowYpos;

	bool daemonEnabled;
	QString daemonListenName;

	int historySize;
	QString historyType;

	QFont font;

	bool useTabBar;

	QString shellProgram;
	QStringList environmentVariables;

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

	void updateMainWindowTitle( QString title );

	void removeTerminalFromList( QTermWidget *terminal = 0 );
	void removeTerminalViaUserClose();

	void changeTransparency( qreal opacity, qreal fadeOpacity );

protected:
	virtual void changeEvent( QEvent *event );
	virtual void resizeEvent( QResizeEvent *event );
	virtual void closeEvent( QCloseEvent *event );

signals:
	void finished();
	void removedTerminal();
};

#endif

