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

#ifndef __BAULKEMBED_H
#define __BAULKEMBED_H

#include <QCloseEvent>
#include <QHBoxLayout>
#include <QX11EmbedContainer>

#include "baulkwidget.h"

//! Baulk reimplementation of BaulkWidget for X11 Embedding
/*!
 * Mainly used for the tiling of X11 Windows
 * TODO Known Issues:
 *  - Pidgin Buddy Window Hiding (click on the System Tray Icon), XEmbed Still thinks window is there, but its not, and it does not come back
 */
class BaulkEmbed : public BaulkWidget {
	Q_OBJECT

public:
	//! Default Constructor
	BaulkEmbed( BaulkWidget *parent = 0 );

	//! Window ID Convenience Constructor
	BaulkEmbed( WId windowID, BaulkWidget *parent = 0 );

	//! Destructor
	~BaulkEmbed();

	//-- Accessors
	WId embedWindowID() const { return embedContainer->clientWinId(); }
	
	//-- Helpers

	//-- Mutators
	void embedWindow( WId windowID );
	void removeEmbedWindow();

private:
	//-- Variables
	QX11EmbedContainer *embedContainer;
	
	//-- Functions
	void initialize();

private slots:
	void testSlot();

protected:
	void closeEvent( QCloseEvent *event );
};

#endif

