// Common - Compositing Handles from X11
//
// Baulk - Copyright (C) 2008  Jacob Alexander
//
// Initial code is taken from the Qt 4 graphics dojo examples
//  at http://labs.trolltech.com 
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

#ifndef __COMPOSITING_H
#define __COMPOSITING_H

#ifdef Q_WS_X11

#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>

void getDisplayInformation( Display*& display , Visual*& visual , Colormap& colormap )
{
	display = XOpenDisplay( 0 ); // open default display
	if ( !display ) {
		qWarning("Cannot connect to the X server");
		exit( 1 );
	}

	int screen = DefaultScreen(display);
	int eventBase, errorBase;

	if ( XRenderQueryExtension( display, &eventBase, &errorBase ) ) {
		int nvi;

		XVisualInfo templ;

		templ.screen  = screen;
		templ.depth = 32;
		templ.c_class = TrueColor;

		XVisualInfo *xvi = XGetVisualInfo(
				display, 
				VisualScreenMask | VisualDepthMask | VisualClassMask, 
				&templ, 
				&nvi);
	
		for ( int i = 0; i < nvi; ++i ) {
			XRenderPictFormat* format = XRenderFindVisualFormat( display, xvi[i].visual );

			if ( format->type == PictTypeDirect && format->direct.alphaMask ) {
				visual = xvi[i].visual;
				colormap = XCreateColormap( 
						display, 
						RootWindow( display, screen ), 
						visual, 
						AllocNone );

				// found ARGB visual
				break;
			}
		}
	}
}

#endif

#endif

