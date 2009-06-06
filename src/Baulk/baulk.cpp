// Baulk
//
// Baulk - Copyright (C) 2008-2009 - Jacob Alexander
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

#include "baulk.h"

// Constructor ************************************************************************************
Baulk::Baulk( QObject *parent ) : QObject( parent ) {

	QScriptEngine engine;
	// Baulk Script
	engine.globalObject().setProperty( "UnifiedInterface", engine.scriptValueFromQMetaObject<UnifiedInterface>() );

	// Start Scripting Engine
	QString scriptFileName("baulkscript.js"); // TODO Place with configs
	QFile scriptFile( scriptFileName );
	scriptFile.open( QIODevice::ReadOnly );
	engine.evaluate( scriptFile.readAll(), scriptFileName );
	scriptFile.close();

	if ( engine.hasUncaughtException() ) {
		qDebug( tr("BaulkScript has blown up in your face!").toUtf8() );
		qDebug( tr("%1 | %2").arg( engine.uncaughtException().toString() ).arg( engine.uncaughtExceptionBacktrace().join("\n") ).toUtf8() );
	}

	///////////// Screen Info
	qDebug( "Number of Screens %d" , qApp->desktop()->numScreens() );
	// TODO Change to settings or dynamic (-1 is default screen)
	QRect currentScreenSize = qApp->desktop()->availableGeometry( -1 );
	qDebug( "%d", currentScreenSize.width() );

}

// Log Update *************************************************************************************
bool Baulk::updateMsgLogs( QStringList msgLogs ) {
	// TODO Redo
	return true;
}

// Command Line Arguments *************************************************************************
bool Baulk::processCommandArgs() {
	// TODO Redo
	return true;
}

