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

#include "baulkxml.h"
#include "libraryloader.h"

// Constructor
LibraryLoader::LibraryLoader( QObject *parent ) : QLibrary( parent ) {
	BaulkXML xmlConfig( "BaulkLibs", this );

	// Default Library Directory Search - In order
	libraryDirs = QStringList()
		<< "BaulkLibs"			// Build Directory
		<< "/usr/local/lib/BaulkLibs"
		<< "/usr/lib/BaulkLibs";

	// Override Library Search if Configuration Found
	if ( xmlConfig.loadSuccessful() ) {
		QVariant tmp;
		tmp = xmlConfig.option("libraryList");
		libraryDirs = tmp.isNull() ? libraryDirs : tmp.toStringList();
	}

	// Revise Library Directory List
	QDir dir;
	for ( int c = 0; c < libraryDirs.count(); ++c )
		if ( !dir.exists( libraryDirs[ c ] ) )
			libraryDirs.removeAt( c );

	if ( libraryDirs.count() < 1 )
		qCritical( tr("Library Loader\n|No library directories could be found").toUtf8() );
}

// Error List
QStringList LibraryLoader::errorList() const {
	return allErrors;
}

// Library Loaders
bool LibraryLoader::loadLibrary( QString libraryName ) {
	setFileName( determineLibraryPath( libraryName ) );
	bool success = load();
	if ( !success )
		allErrors << errorString();
	return success;
}

bool LibraryLoader::loadLibrary( QString libraryName, int versionNumber ) {
	setFileNameAndVersion( determineLibraryPath( libraryName ), versionNumber );
	bool success = load();
	if ( !success )
		allErrors << errorString();
	return success;
}

bool LibraryLoader::loadLibrary( QString libraryName, bool detectVersion, QString versionNumber ) {
	if ( detectVersion )
		setFileName( determineLibraryPath( libraryName ) ); // TODO - Implement version detection here
	else
		setFileNameAndVersion( determineLibraryPath( libraryName ), versionNumber );

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

// Gives the full path to the detected Baulk Library
QString LibraryLoader::determineLibraryPath( QString libraryName ) {
	for ( int c = 0; c < libraryDirs.count(); ++c ) {
		QString dir = libraryDirs[ c ] + "/" + libraryName;
		if ( isLibrary( dir ) )
			return dir;
	}
	qFatal( tr("Library Loader\n|Could not find specified Library\n||%1").arg( libraryName ).toUtf8() );
	return "";
}

// Checks for Baulk Library Existance 
bool LibraryLoader::exists( QString libraryName ) {
	return isLibrary( determineLibraryPath( libraryName ) );
}
