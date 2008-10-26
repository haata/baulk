// Baulk - WebBaulk - Web Browser for Baulk
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	webbaulk.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	A WebKit browser for Baulk, using a vim control scheme
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

#include <QVBoxLayout>
#include <QtWebKit>
#include <QWebView>

#include <baulkwidget.h>

class WebBaulk : public BaulkWidget {
	Q_OBJECT

public:
	WebBaulk( QWidget *parent = 0 );

private:
	QWebView *webview;
};

#endif

