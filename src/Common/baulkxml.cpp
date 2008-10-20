// Baulk - Common - Baulk XML Configuration Reader/Writer
//
// Baulk - Copyright (C) 2008 - Jacob Alexander
//
//  File:	baulkxml.cpp
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

BaulkXML::BaulkXML( QString configName, QObject *parent ) : QObject( parent ) {
	// Prepare Config Directory
	configDir.mkdir( QDir::homePath() + "/.config/Baulk");
	configDir.setPath( QDir::homePath() + "/.config/Baulk");
	configFile.setFileName( QString("%1/%2.xml").arg( configDir.path() ).arg( configName ) );

	// Loads the XML document
	xmlDoc = new QDomDocument( configName );

	// Default Profile
	currentProfile = "default";

	loaded = loadConfig( configName );
}

BaulkXML::~BaulkXML() {
	delete xmlDoc;
}

// Saves the config to disk
bool BaulkXML::saveConfig() {
	prepareConfig();

	if ( configFile.open( QIODevice::WriteOnly ) ) {
		QTextStream output( &configFile );
		output << xmlDoc->toString();
	}
	else {
		qWarning( tr("BaulkXML\n\t|Could not open config file\n\t||%1").arg( configFile.fileName() ).toUtf8() );
		return false;
	}

	configFile.close();
	return true;
}

// Loads the config from disk
bool BaulkXML::loadConfig( QString configName ) {
	if ( configFile.open( QIODevice::ReadOnly ) ) {
		if ( !xmlDoc->setContent( &configFile ) ) {
			qCritical( tr("BaulkXML\n\t|Could not load XML document\n\t||%1").arg( configFile.fileName() ).toUtf8() );
			return false;
		}
	}
	else {
		qCritical( tr("BaulkXML\n\t|Could not open config file\n\t||%1").arg( configFile.fileName() ).toUtf8() );
		return false;
	}

	configFile.close();
	return true;
}

// Loads a setting by its name from the XML
QVariant BaulkXML::option( QString settingName, bool warnOnNotFound ) {
	prepareConfig();

	// Find Setting
	bool found = false;
	for ( xmlDocElementSetting = xmlDocElementProfile.firstChild().toElement(); 
			!xmlDocElementSetting.isNull();
			xmlDocElementSetting = xmlDocElementSetting.nextSibling().toElement() )
		if ( xmlDocElementSetting.tagName() == settingName ) {
			found = true;
			break;
		}
	if ( !found ) {
		qWarning( tr("BaulkXML\n\t|Could not find setting\n\t||%1").arg( settingName ).toUtf8() );
		return QVariant("");
	}

	// Load Setting Data
	xmlDocElementSettingText = xmlDocElementSetting.firstChild().toText();
	if ( !xmlDocElementSettingText.isNull() )
		return QVariant( xmlDocElementSettingText.data() );

	// Some Configurations option will want a null value
	if ( warnOnNotFound )
		qWarning( tr("BaulkXML\n\t|Could not load setting\n\t||%1").arg( settingName ).toUtf8() );

	return QVariant("");
}

bool BaulkXML::loadSuccessful() {
	return loaded;
}

// XML Preparation
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

// Add/Update an option in the XML
void BaulkXML::setOption( QString settingName, QVariant value ) {
	prepareConfig();

	// Find Setting
	bool found = false;
	for ( xmlDocElementSetting = xmlDocElementProfile.firstChild().toElement(); 
			!xmlDocElementSetting.isNull();
			xmlDocElementSetting = xmlDocElementSetting.nextSibling().toElement() )
		if ( xmlDocElementSetting.tagName() == settingName ) {
			found = true;
			break;
		}
	if ( !found ) {
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
}

void BaulkXML::setProfile( QString profileName ) {
	currentProfile = profileName;
}

