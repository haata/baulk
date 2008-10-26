// Baulk - Common - Baulk Console Output Handler
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	handler.h
//  Author(s):	Jacob Alexander (HaaTa)
//
//  Description: 
//	Process all console output in Baulk Executables
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

#ifndef __HANDLER_H
#define __HANDLER_H

#include <iostream>

#include <QRegExp>
#include <QStringList>

QStringList msgLogs;

// Handles all messages sent by the application
void handler( QtMsgType type, const char *msg ) {
	QString log = "";
	QString logPlain = "";
	QString css = 	"<style type=\"text/css\">"
				"body {"
					"margin: 0px;"
					"padding: 0px;"
					"color: white;"
				"}"
				"li {"
					"margin-left: 20px;"
					"margin-top: 0px;"
					"margin-bottom: 0px;"
					"color: white;"
				"}"
			"</style>";
	switch ( type ) {
	case QtDebugMsg:
		log = QObject::tr("%1<font color=\"green\">&lt;Debug&gt; %2<br></font>")
			.arg( css )
			.arg( QString( msg )
				.replace( QRegExp("\t(.*)\n"), QString("<li>\\1</li>") ) 
				.replace( QRegExp("\t(.*)"), QString("<li>\\1</li>") ) 
			);
#ifndef BAULK
		logPlain = QObject::tr("<Debug> %1").arg( msg );
		std::cerr << logPlain.toUtf8().data() << std::endl;
#endif
		break;
	case QtWarningMsg:
		log = QObject::tr( "%1<font color=\"orange\">&lt;Warning&gt; %2<br></font>")
			.arg( css )
			.arg( QString( msg )
				.replace( QRegExp("\t(.*)\n"), QString("<li>\\1</li>") ) 
				.replace( QRegExp("\t(.*)"), QString("<li>\\1</li>") ) 
			);
#ifndef BAULK
		logPlain = QObject::tr("<Warning> %1").arg( msg );
		std::cerr << logPlain.toUtf8().data() << std::endl;
#endif
		break;
	case QtCriticalMsg:
		log = QObject::tr("%1<font color=\"red\">&lt;Critical&gt; %2<br></font>")
			.arg( css )
			.arg( QString( msg )
				.replace( QRegExp("\t(.*)\n"), QString("<li>\\1</li>") ) 
				.replace( QRegExp("\t(.*)"), QString("<li>\\1</li>") ) 
			);
		logPlain = QObject::tr("<Critical> %1").arg( msg );
		std::cerr << logPlain.toUtf8().data() << std::endl;
		break;
	case QtFatalMsg:
		log = QObject::tr("%1<font color=\"red\" font-size=\"large\">&lt;Fatal&gt; %2<br></font>")
			.arg( css )
			.arg( QString( msg )
				.replace( QRegExp("\t(.*)\n"), QString("<li>\\1</li>") ) 
				.replace( QRegExp("\t(.*)"), QString("<li>\\1</li>") ) 
			);
		logPlain = QObject::tr("<Fatal> %1").arg( msg );
		std::cerr << logPlain.toUtf8().data() << std::endl;
		break;
	}

	msgLogs << log;
	
#ifdef BAULK
	if ( baulk != 0 ) {
		if ( baulk->updateMsgLogs( msgLogs ) )
			msgLogs.clear();
	}
#endif
}

#endif

