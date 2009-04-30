// Baulk - Common - Baulk XML Configuration Reader/Writer
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
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

#ifndef __BAULKXML_H
#define __BAULKXML_H

#include <QDir>
#include <QDomAttr>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QObject>
#include <QTextStream>
#include <QVariant>

//! Reads/Writes custom XML Configuration files for Baulk.
/*!
 * Custom XML Configuration class for reading and writing configuration files in Baulk and its sub-projects
 */
class BaulkXML : public QObject {
	Q_OBJECT

public:
	BaulkXML( QString configName, QObject *parent = 0 );
	~BaulkXML();

	//! Save Config to Disk
	bool saveConfig();

	//! Checks for successful XML load
	bool loadSuccessful();

	//! Load Option
	QVariant option( QString settingName, QString propertyKey = "", QVariant property = QVariant(""), bool warnOnNotFound = true );
	//! Save Option
	void setOption( QString settingName, QVariant value, QString propertyKey = "", QVariant properties = QVariant("") );

	//! Current Profile
	/*!
	 * Profiles allow for different sets of options in the same configuration file.
	 */
	QString profile();
	//! Set options profile to use
	void setProfile( QString profileName );

private:
	bool loadConfig( QString configName );
	bool loaded;

	QString errorName() const { return tr("BaulkXML"); }

	bool settingSearch( QString settingName, QString propertyKey = "", QVariant property = QVariant("") );

	QDir configDir;
	QDomAttr xmlDocElementProperty;
	QDomDocument *xmlDoc;
	QDomElement xmlDocElementProfile;
	QDomElement xmlDocElementRoot;
	QDomElement xmlDocElementSetting;
	QDomText xmlDocElementSettingText;
	QFile configFile;
	QString currentProfile;

	QStringList msgList;

	void prepareConfig();
};

#endif

