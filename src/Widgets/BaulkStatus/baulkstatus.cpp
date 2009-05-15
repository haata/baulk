// Baulk - Baulk Status - Information About the Current Window Instance of Baulk
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//   <haata at users.sf.net>
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

#include "baulkstatus.h"

// Constructors ***********************************************************************************
BaulkStatus::BaulkStatus( BaulkWidget *parent ) : BaulkWidget( parent ) {
	// Layout
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setContentsMargins( 0,0,0,0 );
	setLayout( layout );

	// Text Browser
	messageBrowser = new QTextBrowser;
	messageBrowser->setStyleSheet("QTextBrowser {"
			"background: black;"
			"selection-background-color: darkgray;"
			"}");
	layout->addWidget( messageBrowser );
	setFocusProxy( messageBrowser );

	// Connections
	connect( parent, SIGNAL( msgLogsUpdated( QStringList ) ), this, SLOT( updateMsgLog( QStringList ) ) );
}


// Private Slots **********************************************************************************
void BaulkStatus::updateMsgLog( QStringList msgLogs ) {
	QStringList temp = current;
	if ( current.count() < msgLogs.count() )
		for ( int c = current.count(); c < msgLogs.count(); ++c )
			temp.append( msgLogs[c] );
	else
		qCritical("BaulkStatus\n\tYour logs are disappearing?!");

	current = temp;
	messageBrowser->setHtml( current.join("") );
}

