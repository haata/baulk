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
Baulk::Baulk( QWidget *parent ) : QObject( (QObject*) parent ) { // TODO Parent

	QScriptEngine engine;
	// Baulk Script
	engine.globalObject().setProperty( "UnifiedInterface", engine.scriptValueFromQMetaObject<UnifiedInterface>() );

	// Start Scripting Engine
	QString scriptFileName("baulkscript.js"); // TODO Place with configs
	QFile scriptFile( scriptFileName );
	scriptFile.open( QIODevice::ReadOnly );
	engine.evaluate( scriptFile.readAll(), scriptFileName );
	scriptFile.close();

	if ( engine.hasUncaughtException() )
		qDebug("ARG!");

	///////////// Screen Info
	qDebug( "Number of Screens %d" , qApp->desktop()->numScreens() );
	// TODO Change to settings or dynamic (-1 is default screen)
	QRect currentScreenSize = qApp->desktop()->availableGeometry( -1 );
	qDebug( "%d", currentScreenSize.width() );

#if 0
	UnifiedInterface test( this );
	test.regexFilterWindowName( QRegExp(".*Nokia.*") );
	test.logPrintIDList( test.filteredList() );
	//QWidget *resre = new QWidget( );
	//resre->show();

	//XCBWindowManipulation *windowManipulator = new XCBWindowManipulation( scanner.serverConnection(), this );
	QRect recta( 5,5,600,800 );
	//scanner.resizeWindow( scanner.filteredList()[0].id, recta );
	test.moveWindow( UnifiedInterface::listStringToWindowID( test.filteredList()[0] ), 0, recta.topLeft() );
	//windowManipulator->setWindowBorder( scanner.filteredList()[0].id, 0 );
	//windowManipulator->setUserFocus( scanner.filteredList()[0].id );
	//BaulkEmbed *tets = new BaulkEmbed( (WId)scanner.filteredList()[0].id );
	//qDebug( "%d", currentScreenSize.width() );
	//QRect tmp2 = currentScreenSize;
	//tmp2.setLeft( tmp2.width() / 2 );
	//tets->setGeometry( tmp2 );
	//tets->show();
#endif
}

// Window Close Event *****************************************************************************
void Baulk::closeEvent( QCloseEvent *event ) {
	//event->ignore();
	
	// TODO - Send Event to Controller for quit/save message
	// 		Use controller infoClient inorder to determine whether or not to kill the server
	/*	
	bool (*allowQuit)();
	allowQuit = (bool(*)()) library->lrResolve("allowQuit");

	if ( allowQuit() ) {
		qDebug("Closing");
		event->accept();
	}
	else event->ignore();
	*/
}

// Log Update *************************************************************************************
bool Baulk::updateMsgLogs( QStringList msgLogs ) {
	if ( controller != 0 ) {
		controller->setMsgLogs( msgLogs );
		return true;
	}
	return false;
}

// Command Line Arguments *************************************************************************
bool Baulk::processCommandArgs() {
	return controller->processCommandArgs();
}

// SLOTS ******************************************************************************************
void Baulk::setWindowTitleName( QString windowTitle ) {
	//setWindowTitle( windowTitle );
}

