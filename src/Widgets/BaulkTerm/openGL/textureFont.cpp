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

#include "textureFont.h"

// Constructors ***********************************************************************************
TextureFont::TextureFont( QString inputText, QFont font, QColor textColor ) {
	textureText = inputText;
	renderFont = font;
	textureForegroundColor = textColor;

	generateTexture();
}

TextureFont::~TextureFont() {
	delete textureFontInfo;
	delete textureImage;
}

// Accessors **************************************************************************************
QImage *TextureFont::outputImage() const {
	return textureImage;
}

int TextureFont::pixelHeight() const {
	return textureFontInfo->lineSpacing();
}

int TextureFont::pixelWidth() const {
	return textureFontInfo->maxWidth();
}

QColor TextureFont::outputColor() const {
	return textureForegroundColor;
}

QFont TextureFont::outputFont() const {
	return renderFont;
}

QString TextureFont::outputText() const {
	return textureText;
}

// Mutators ***************************************************************************************
void TextureFont::setColor( QColor color ) {
	textureForegroundColor = color;

	renderText();
}

void TextureFont::setFont( QFont font ) {
	renderFont = font;

	delete textureFontInfo;
	delete textureImage;

	generateTexture();
}

void TextureFont::setInputText( QString inputText ) {
	int oldSize = textureText.size();
	textureText = inputText;

	// Only create a new QImage if needed
	if ( oldSize != textureText.size() ) {
		delete textureFontInfo;
		delete textureImage;
		generateTexture();
	}
	else renderText();
}

// QImage Generator *******************************************************************************
void TextureFont::generateTexture() {
	// Font Information
	textureFontInfo = new QFontMetrics( renderFont );

	// Generate base image
	textureImage = new QImage( textureFontInfo->maxWidth() * textureText.size(),
			textureFontInfo->lineSpacing(),
			QImage::Format_ARGB32_Premultiplied );

	renderText();
}

void TextureFont::renderText() {
	// Set background as transparent
	textureImage->fill( qRgba( 255, 255, 255, 0 ) );

	// Render text with QPainter
	QPainter painter;
	painter.begin( textureImage );
	painter.setPen( textureForegroundColor );
	painter.setFont( renderFont );
	painter.drawText( 0, textureFontInfo->overlinePos(), textureText );
	painter.end();
}

