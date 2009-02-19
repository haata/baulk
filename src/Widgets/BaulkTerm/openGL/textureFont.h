// Baulk - Qt Font Texture Generator
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

#ifndef __TEXTUREFONT_H
#define __TEXTUREFONT_H

#include <QColor>
#include <QFont>
#include <QFontMetrics>
#include <QImage>
#include <QPainter>

/**
 * @author Jacob Alexander (HaaTa)
 *
 * Generates Font Texture for use with OpenGL surfaces.
 * The background of each texture image is transparent.
 * Uses QImage
 */

class TextureFont {
public:
	// Constructors
	TextureFont( QString inputText, QFont font = QFont(), QColor textColor = QColor( "#000000" ));
	~TextureFont();

	// Accessors
	QImage *outputImage() const;
	int pixelHeight() const;
	int pixelWidth() const;

	QColor outputColor() const;
	QFont outputFont() const;
	QString outputText() const;

	// Mutators
	void setColor( QColor color );
	void setFont( QFont font );
	void setInputText( QString inputText );

private:
	// Variables
	QColor textureForegroundColor;
	QFont renderFont;
	QFontMetrics *textureFontInfo;
	QString textureText;

	QImage *textureImage;

	// QImage Generator
	void generateTexture();

	// Text Render
	void renderText();
};

#endif

