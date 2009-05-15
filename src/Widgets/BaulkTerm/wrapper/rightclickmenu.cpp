// Baulk - BaulkTerm Right Click Menu
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

#include "rightclickmenu.h"

// Constructor ************************************************************************************
BaulkTermRightClickMenu::BaulkTermRightClickMenu( QWidget *parent ) : QMenu( parent ) {
	// Menu Settings
	setStyleSheet("QWidget {"
				"background: grey;"
				"}");

	// Initialize Actions
	copyAction = new QAction( tr("Copy"), this );
	fontAction = new QAction( tr("Set Font"), this );
	pasteAction = new QAction( tr("Paste"), this );
	transparencyAction = new QAction( tr("Set Transparency"), this );

	// Attach Actions
	addAction( copyAction );
	addAction( pasteAction );
	addSeparator();
	addAction( fontAction );
	addAction( transparencyAction );

	// Connections
	connect( fontAction, SIGNAL( triggered() ), SLOT( fontDialog() ) );
	connect( transparencyAction, SIGNAL( triggered() ), SLOT( transparencyDialog() ) );
}

// Fonts ******************************************************************************************
void BaulkTermRightClickMenu::fontDialog() {
	bool ok;

	// Font Dialog
	QFont font = QFontDialog::getFont( &ok, QFont( "Monospace", 10 ), this );

	if ( ok )
		emit newFont( font );
}

// Opacity ****************************************************************************************
void BaulkTermRightClickMenu::transparencyDialog() {
	// Dialog Window
	BaulkDialog *dialog = new BaulkDialog( true, this );

	// Labels
	QLabel *mainLabel = new QLabel( tr("Main Transparency") );
	mainLabel->setWordWrap( true );
	QLabel *fadeLabel = new QLabel( tr("Fade Transparency") );
	fadeLabel->setWordWrap( true );
	QLabel *noteLabel = new QLabel( tr("<b>Note:</b> A composite manager must be running to use these options (ie. xcompmgr).") );
	noteLabel->setWordWrap( true );

	// Spin Boxes
	QDoubleSpinBox *mainTransparencySpinBox = new QDoubleSpinBox;
	mainTransparencySpinBox->setDecimals( 2 );
	mainTransparencySpinBox->setMaximum( 1 );
	mainTransparencySpinBox->setMinimum( 0 );

	QDoubleSpinBox *fadeTransparencySpinBox = new QDoubleSpinBox;
	fadeTransparencySpinBox->setDecimals( 2 );
	fadeTransparencySpinBox->setMaximum( 1 );
	fadeTransparencySpinBox->setMinimum( 0 );

	// Button Box
	QDialogButtonBox *buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel );
	connect( buttonBox, SIGNAL( accepted() ), dialog, SLOT( accept() ) );
	connect( buttonBox, SIGNAL( rejected() ), dialog, SLOT( forceClose() ) );

	// Dialog Settings
	dialog->setWindowTitle( tr("Adjust Terminal Transparency") );

	// Dialog Layout
	QVBoxLayout *mainSpinBoxLayout = new QVBoxLayout;
	mainSpinBoxLayout->addWidget( mainLabel );
	mainSpinBoxLayout->addWidget( mainTransparencySpinBox );

	QVBoxLayout *fadeSpinBoxLayout = new QVBoxLayout;
	fadeSpinBoxLayout->addWidget( fadeLabel );
	fadeSpinBoxLayout->addWidget( fadeTransparencySpinBox );

	QHBoxLayout *mainOptionLayout = new QHBoxLayout;
	mainOptionLayout->addLayout( mainSpinBoxLayout );
	mainOptionLayout->addLayout( fadeSpinBoxLayout );

	QVBoxLayout *mainDialogLayout = new QVBoxLayout;
	mainDialogLayout->addLayout( mainOptionLayout );
	mainDialogLayout->addWidget( noteLabel );
	mainDialogLayout->addWidget( buttonBox );

	dialog->setLayout( mainDialogLayout );

	dialog->show();

	qreal main = 0.2;
	qreal fade = 0.3;
	qDebug("AAAA");

	emit newTransparency( main, fade );
}

