// Baulk - Common - Library Loader
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	libraryloader.cpp
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

#include "libraryloader.h"

// Constructor
LibraryLoader::LibraryLoader( QObject *parent ) : QLibrary( parent ) {
	// Determine/Add potential library directories (From XML Config File)
	// and check if they exist before adding to the list
}

// Error List
QStringList LibraryLoader::errorList() const {
	return allErrors;
}

// Library Loaders
bool LibraryLoader::loadLibrary( QString libraryName ) {
	setFileName( libraryName );
	bool success = load();
	if ( !success )
		allErrors << errorString();
	return success;
}

bool LibraryLoader::loadLibrary( QString libraryName, int versionNumber ) {
	setFileNameAndVersion( libraryName, versionNumber );
	bool success = load();
	if ( !success )
		allErrors << errorString();
	return success;
}

bool LibraryLoader::loadLibrary( QString libraryName, QString versionNumber ) {
	setFileNameAndVersion( libraryName, versionNumber );
	bool success = load();
	if ( !success )
		allErrors << errorString();
	return success;
}

// Less Restrictive Symbol Resolver
void *LibraryLoader::lrResolve( QString symbol ) {
	const char *symbolName = symbol.toAscii().data(); 
	void *tmp = resolve( symbolName );
	if ( allErrors.last() != errorString() )
		allErrors << errorString();
	return tmp;
}

