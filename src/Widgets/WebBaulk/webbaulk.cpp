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

#include "webbaulk.h"

WebBaulk::WebBaulk( QWidget *parent ) : BaulkWidget( parent ) {
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins( 0,0,0,0 );
	setLayout( layout );

	webview = new QWebView( parent );
	webview->load( QUrl("http://google.ca") );
	setFocusProxy( webview );

	layout->addWidget( webview );
}

