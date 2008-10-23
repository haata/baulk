// Baulk - Common - Library Loader
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	libraryloader.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	Streamlined Library Loader for Baulk
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

#ifndef __LIBRARYLOADER_H
#define __LIBRARYLOADER_H

#include <QDir>
#include <QLibrary>
#include <QStringList>

#include "baulkwidget.h"

class LibraryLoader : public QLibrary {
	Q_OBJECT

public:
	LibraryLoader( QObject *parent = 0 );
	
	// A list of all errors since initialization, not accurate when using QLibrary directly (unless function reimplemented)
	QStringList errorList() const;

	// Returns true if a library exists
	// 	Assumes Baulk library directories
	bool exists( QString libraryName );

	// Loads the Library, returns true if successful, false otherwise
	// 	Assumes Baulk library directories
	bool loadLibrary( QString libraryName );
	bool loadLibrary( QString libraryName, int versionNumber );
	bool loadLibrary( QString libraryName, bool detectVersion, QString version = "" ); // Uses Baulk Control as required version by default

	// Less Restrictive Symbol Resolver, provided for convenience, be careful using it
	void *lrResolve( QString symbol );

	// Returns a list of loadable libraries in the preferred library directory
	QStringList loadableLibraries();

	// BaulkControl Simplified Loaders
	BaulkWidget *mainWidget();
	QObject *mainObject();

private:
	QString determineLibraryPath( QString libraryName );

	void updateErrorList();

	QStringList allErrors;
	QStringList libraryDirs;
	QStringList libraryFilters;
};

#endif

