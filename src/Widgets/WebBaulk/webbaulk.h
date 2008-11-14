// Baulk - WebBaulk - Web Browser for Baulk
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

#ifndef __WEBBAULK_H
#define __WEBBAULK_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSplitter>
#include <QStackedWidget>
#include <QStringList>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QtWebKit>
#include <QVBoxLayout>
#include <QWebHistory>
#include <QWebSettings>
#include <QWebView>

#include <baulkwidget.h>

#include "common.h"

/**
 * @author Jacob Alexander (HaaTa)
 *
 * A WebKit browser for Baulk, using a vim control scheme
 */
class WebBaulk : public BaulkWidget {
	Q_OBJECT

public:
	WebBaulk( QWidget *parent = 0 );

private:
	// Current WebView
	QWebView *webview;

	// Convenience Widgets
	QLabel *loadLabel;
	QLineEdit *addressBarLineEdit;
	ToolButton *backToolButton;
	ToolButton *nextToolButton;
	ToolButton *refreshToolButton;
	ToolButton *stopToolButton;
	ToolButton *newTabToolButton;
	ToolButton *nextTabToolButton;
	ToolButton *previousTabToolButton;

	// Information Viewer
	QStackedWidget *infoLayer;
	QTreeWidget *tabTree;

	// Tabs
	QStackedWidget *tabLayer;

	// Misc
	QSplitter *subLayout;
	QVBoxLayout *mainLayout;

	// Top Bar Setup
	void topBarSetup();

	// Information Viewer Setup
	void infoViewerSetup();

private slots:
	// URL
	void acceptUrl();
	void updateUrl( QUrl url );

	// Status
	void statusUpdate( int progress );

	// Tabs
	void nextTab();
	void prevTab();
	void newTab();

	// Title
	void updateTabTitle( QString title );
};

#endif

