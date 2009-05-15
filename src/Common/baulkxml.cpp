// Baulk - Common - Baulk XML Configuration Reader/Writer
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
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

#include "baulkxml.h"

// Constructors ***********************************************************************************
BaulkXML::BaulkXML( QString configName, QObject *parent ) : QObject( parent ) {
	// Prepare Config Directory
#ifdef Q_OS_WIN32
	configDir.mkpath( QDir::homePath() + "/config/Baulk");
	configDir.setPath( QDir::homePath() + "/config/Baulk");
	configFile.setFileName( QString("%1/%2.xml").arg( configDir.path() ).arg( configName ) );
#else
	configDir.mkpath( QDir::homePath() + "/.config/Baulk");
	configDir.setPath( QDir::homePath() + "/.config/Baulk");
	configFile.setFileName( QString("%1/%2.xml").arg( configDir.path() ).arg( configName ) );
#endif

	// Loads the XML document
	xmlDoc = new QDomDocument( configName );

	// Default Profile
	currentProfile = "default";

	// Flag storing successful loading of the xml
	loaded = loadConfig( configName );
}

BaulkXML::~BaulkXML() {
	delete xmlDoc;
}

// Saves the config to disk ***********************************************************************
bool BaulkXML::saveConfig() {
	prepareConfig();

	if ( configFile.open( QIODevice::WriteOnly ) ) {
		QTextStream output( &configFile );
		output << xmlDoc->toString();
	}
	else {
		qWarning( tr("%1\n\tCould not open config file\n\t%2")
				.arg( errorName() )
				.arg( configFile.fileName() )
			.toUtf8() );
		return false;
	}

	configFile.close();
	return true;
}

// Loads the config from disk *********************************************************************
bool BaulkXML::loadConfig( QString configName ) {
	if ( configFile.open( QIODevice::ReadOnly ) ) {
		if ( !xmlDoc->setContent( &configFile ) ) {
			qCritical( tr("%1\n\tCould not load XML document\n\t%2")
					.arg( errorName() )
					.arg( configFile.fileName() )
				.toUtf8() );
			return false;
		}
	}
	else {
		qWarning( tr("%1\n\tCould not load config file\n\t%2 - %3")
				.arg( errorName() )
				.arg( configFile.fileName() )
				.arg( configFile.errorString() )
			.toUtf8() );
		return false;
	}

	configFile.close();
	return true;
}

// Loads a setting by its name from the XML *******************************************************
QVariant BaulkXML::option( QString settingName, QString propertyKey, QVariant property, bool warnOnNotFound ) {
	prepareConfig();

	if ( !settingSearch( settingName, propertyKey, property ) ) {
		if ( property == QVariant() || propertyKey == "" )
			qWarning( tr("%1\n\tCould not find setting\n\t%2")
					.arg( errorName() )
					.arg( settingName )
				.toUtf8() );
		else
			qWarning( tr("%1\n\tCould not find setting\n\t%2 - %3 - %4")
					.arg( errorName() )
					.arg( settingName )
					.arg( propertyKey )
					.arg( property.toString() )
				.toUtf8() );
		return QVariant("");
	}
	
	// Load Setting Data
	xmlDocElementSettingText = xmlDocElementSetting.firstChild().toText();
	if ( !xmlDocElementSettingText.isNull() )
		return QVariant( xmlDocElementSettingText.data() );

	// Some Configuration options will want a null value
	if ( warnOnNotFound )
		qWarning( tr("%1\n\tCould not load setting\n\t%2")
				.arg( errorName() )
				.arg( settingName )
			.toUtf8() );

	return QVariant("");
}

// Prepares XML Variables for option/property extraction
bool BaulkXML::settingSearch( QString settingName, QString propertyKey, QVariant property ) {
	// Find Setting
	for ( xmlDocElementSetting = xmlDocElementProfile.firstChild().toElement(); 
			!xmlDocElementSetting.isNull();
			xmlDocElementSetting = xmlDocElementSetting.nextSibling().toElement() )
		if ( xmlDocElementSetting.tagName() == settingName ) {
			if ( propertyKey == "" )
				return true;
			xmlDocElementProperty = xmlDocElementSetting.attributeNode( propertyKey );
			if ( xmlDocElementProperty.value() == property.toString() )
				return true;
		}
	// Not Found
	return false;
}

// Successful Load of Config **********************************************************************
bool BaulkXML::loadSuccessful() {
	return loaded;
}

// XML Preparation ********************************************************************************
void BaulkXML::prepareConfig() {
	// Find Root - Profiles
	if ( xmlDoc->documentElement().tagName() != "Profiles" ) {
		xmlDocElementRoot = xmlDoc->createElement("Profiles");
		xmlDoc->appendChild( xmlDocElementRoot );
	}
	else xmlDocElementRoot = xmlDoc->documentElement();

	// Find Profile - "currentProfile"
	bool found = false;
	for ( xmlDocElementProfile = xmlDocElementRoot.firstChild().toElement(); 
			!xmlDocElementProfile.isNull();
			xmlDocElementProfile = xmlDocElementProfile.nextSibling().toElement() )
		if ( xmlDocElementProfile.tagName() == currentProfile ) {
			found = true;
			break;
		}
	if ( !found ) {
		xmlDocElementProfile = xmlDoc->createElement( currentProfile );
		xmlDocElementRoot.appendChild( xmlDocElementProfile );
	}
}

QString BaulkXML::profile() {
	return currentProfile;
}

// Add/Update an option in the XML ****************************************************************
void BaulkXML::setOption( QString settingName, QVariant value, QString propertyKey, QVariant property ) {
	prepareConfig();

	// Find Setting
	if ( !settingSearch( settingName, propertyKey, property ) ) {
		xmlDocElementSetting = xmlDoc->createElement( settingName );
		xmlDocElementProfile.appendChild( xmlDocElementSetting );
	}

	// Save Setting
	xmlDocElementSettingText = xmlDocElementSetting.firstChild().toText();
	if ( xmlDocElementSettingText.isNull() ) {
		xmlDocElementSettingText = xmlDoc->createTextNode( value.toString() );
		xmlDocElementSetting.appendChild( xmlDocElementSettingText );
	}
	else xmlDocElementSettingText.setData( value.toString() );

	// Set Attribute
	if ( propertyKey != "" )
		xmlDocElementSetting.setAttribute( propertyKey, property.toString() );
}

// Set Config Profile *****************************************************************************
void BaulkXML::setProfile( QString profileName ) {
	currentProfile = profileName;
}

