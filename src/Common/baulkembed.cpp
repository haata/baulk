// Baulk - Baulk Embed Window (X11 XEmbed)
//
// Baulk - Copyright (C) 2009 - Jacob Alexander
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

#include "baulkembed.h"

// Constructors ***********************************************************************************
BaulkEmbed::BaulkEmbed( BaulkWidget *parent ) : BaulkWidget( parent ) {
	initialize();
}

BaulkEmbed::BaulkEmbed( WId windowID, BaulkWidget *parent ) : BaulkWidget( parent ) {
	initialize();
	embedWindow( windowID );
}

void BaulkEmbed::initialize() {
	embedContainer = new QX11EmbedContainer;

	QHBoxLayout *layout = new QHBoxLayout( this );
	layout->setContentsMargins( 0,0,0,0 );
	layout->addWidget( embedContainer );

	setFocusProxy( embedContainer );
	setLayout( layout );
}

// Destructor *************************************************************************************
BaulkEmbed::~BaulkEmbed() {
}

// Embedding Functions ****************************************************************************
void BaulkEmbed::embedWindow( WId windowID ) {
	embedContainer->embedClient( windowID );
}

void BaulkEmbed::removeEmbedWindow() {
	embedContainer->discardClient();
}

// Reimplemented Functions ************************************************************************
void BaulkEmbed::closeEvent( QCloseEvent *event ) {
	removeEmbedWindow();
	event->accept();
}

// TEST *********
void BaulkEmbed::testSlot() {
	qDebug("TESTESSETSET");
	qDebug("%d", (int) embedContainer->clientWinId() );
	if (embedContainer->isVisible() )
		qWarning("AAAAAAAA");
}
