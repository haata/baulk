// Baulk - Baulk Swallow - Widget Embedder/Catcher for X11
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	baulkswallow.cpp
//  Author(s):	Jacob Alexander (HaaTa)
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

#include "baulkswallow.h"

// Constructor ************************************************************************************
BaulkSwallow::BaulkSwallow( BaulkWidget *parent ) : BaulkWidget( parent ) {
	swallow = new QX11EmbedContainer;

	infoLabel = new QLabel( tr("Window ID:") );

	infoLineEdit = new QLineEdit;

	// Window ID Information
	infoLayout = new QHBoxLayout;
	infoLayout->addWidget( infoLabel );
	infoLayout->addWidget( infoLineEdit );
	infoLayout->addStretch();

	// Main Layout
	layout = new QVBoxLayout;
	layout->addLayout( infoLayout );
	layout->addWidget( swallow );
	layout->setContentsMargins( 0,0,0,0 );

	setLayout( layout );
	setFocusProxy( swallow );

	// Window ID is only final after the layout creation is finished
	infoLineEdit->setText( QString("%1").arg( (int) swallow->winId() ) );

	// Connections
	connect( swallow, SIGNAL( clientIsEmbedded() ), this, SLOT( windowSwallowed() ) );
	connect( swallow, SIGNAL( clientClosed() ), this, SLOT( windowCoughed() ) );
}

// Cough / Swallow Slots **************************************************************************
void BaulkSwallow::windowCoughed() {
	// Show Window ID Info
	for ( int c = 0; c < infoHBLayout->count() - 1; ++c ) 
		infoHBLayout->itemAt( c )->widget()->show();
}

void BaulkSwallow::windowSwallowed() {
	// Hide Window ID Info
	for ( int c = 0; c < infoHBLayout->count() - 1; ++c ) 
		infoHBLayout->itemAt( c )->widget()->hide();
}

