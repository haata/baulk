#ifndef _COLOR_TABLE_H
#define _COLOR_TABLE_H

#include "CharacterColor.h"

using namespace Konsole;
//
//static const ColorEntry whiteonblack_color_table[TABLE_COLORS] =
//{
//    // normal
//    ColorEntry(QColor(0xFF,0xFF,0xFF), 0, 0 ), ColorEntry( QColor(0x00,0x00,0x00), 1, 0 ), // Dfore, Dback
//    ColorEntry(QColor(0x00,0x00,0x00), 0, 0 ), ColorEntry( QColor(0xB2,0x18,0x18), 0, 0 ), // Black, Red
//    ColorEntry(QColor(0x18,0xB2,0x18), 0, 0 ), ColorEntry( QColor(0xB2,0x68,0x18), 0, 0 ), // Green, Yellow
//    ColorEntry(QColor(0x18,0x18,0xB2), 0, 0 ), ColorEntry( QColor(0xB2,0x18,0xB2), 0, 0 ), // Blue, Magenta
//    ColorEntry(QColor(0x18,0xB2,0xB2), 0, 0 ), ColorEntry( QColor(0xB2,0xB2,0xB2), 0, 0 ), // Cyan, White
//    // intensiv
//    ColorEntry(QColor(0x00,0x00,0x00), 0, 1 ), ColorEntry( QColor(0xFF,0xFF,0xFF), 1, 0 ),
//    ColorEntry(QColor(0x68,0x68,0x68), 0, 0 ), ColorEntry( QColor(0xFF,0x54,0x54), 0, 0 ),
//    ColorEntry(QColor(0x54,0xFF,0x54), 0, 0 ), ColorEntry( QColor(0xFF,0xFF,0x54), 0, 0 ),
//    ColorEntry(QColor(0x54,0x54,0xFF), 0, 0 ), ColorEntry( QColor(0xFF,0x54,0xFF), 0, 0 ),
//    ColorEntry(QColor(0x54,0xFF,0xFF), 0, 0 ), ColorEntry( QColor(0xFF,0xFF,0xFF), 0, 0 )
//};
//

static const ColorEntry whiteonblack_color_table[TABLE_COLORS] =
{
    // normal
    ColorEntry( QColor(0xD3,0xD3,0xD3), 0, 0 ), // Foreground1
    ColorEntry( QColor(0x00,0x00,0x00), 1, 0 ), // Background1

    ColorEntry( QColor(0x67,0x67,0x67), 0, 0 ), // Black1
    ColorEntry( QColor(0xEA,0x68,0x68), 0, 0 ), // Red1

    ColorEntry( QColor(0xAB,0xCB,0x8D), 0, 0 ), // Green1
    ColorEntry( QColor(0xE8,0xAE,0x5B), 0, 0 ), // Yellow1

    ColorEntry( QColor(0x71,0xC5,0xF4), 0, 0 ), // Blue1
    ColorEntry( QColor(0xE2,0xBA,0xF1), 0, 0 ), // Magenta1

    ColorEntry( QColor(0x21,0xF1,0xEA), 0, 0 ), // Cyan1
    ColorEntry( QColor(0xD3,0xD3,0xD3), 0, 0 ), // White1

    // intensive
    ColorEntry(QColor(0x00,0x00,0x00), 0, 1 ),	// Foreground2
    ColorEntry( QColor(0xD3,0xD3,0xD3), 1, 0 ),	// Background2

    ColorEntry(QColor(0x75,0x75,0x75), 0, 0 ), 	// Black2
    ColorEntry( QColor(0xFF,0x72,0x72), 0, 0 ),	// Red2

    ColorEntry(QColor(0xAF,0xD7,0x8A), 0, 0 ), 	// Green2
    ColorEntry( QColor(0xFF,0xA7,0x5D), 0, 0 ),	// Yellow2

    ColorEntry(QColor(0x67,0xCD,0xE9), 0, 0 ), 	// Blue2
    ColorEntry( QColor(0xEC,0xAE,0xE9), 0, 0 ),	// Magenta2

    ColorEntry(QColor(0x36,0xFF,0xFC), 0, 0 ), 	// Cyan2
    ColorEntry( QColor(0xFF,0xFF,0xFF), 0, 0 )	// White2
};

static const ColorEntry greenonblack_color_table[TABLE_COLORS] =
{
    ColorEntry(QColor(    24, 240,  24),  0, 0), ColorEntry(QColor(     0,   0,   0),  1, 0),  
    ColorEntry(QColor(     0,   0,   0),  0, 0), ColorEntry(QColor(   178,  24,  24),  0, 0), 
    ColorEntry(QColor(    24, 178,  24),  0, 0), ColorEntry(QColor(   178, 104,  24),  0, 0), 
    ColorEntry(QColor(    24,  24, 178),  0, 0), ColorEntry(QColor(   178,  24, 178),  0, 0), 
    ColorEntry(QColor(    24, 178, 178),  0, 0), ColorEntry(QColor(   178, 178, 178),  0, 0), 
    // intensive colors
    ColorEntry(QColor(   24, 240,  24),  0, 1 ), ColorEntry(QColor(    0,   0,   0),  1, 0 ),
    ColorEntry(QColor(  104, 104, 104),  0, 0 ), ColorEntry(QColor(  255,  84,  84),  0, 0 ),
    ColorEntry(QColor(   84, 255,  84),  0, 0 ), ColorEntry(QColor(  255, 255,  84),  0, 0 ),
    ColorEntry(QColor(   84,  84, 255),  0, 0 ), ColorEntry(QColor(  255,  84, 255),  0, 0 ),
    ColorEntry(QColor(   84, 255, 255),  0, 0 ), ColorEntry(QColor(  255, 255, 255),  0, 0 )
};

static const ColorEntry blackonlightyellow_color_table[TABLE_COLORS] = 
{
    ColorEntry(QColor(  0,   0,   0),  0, 0),  ColorEntry(QColor( 255, 255, 221),  1, 0),  
    ColorEntry(QColor(  0,   0,   0),  0, 0),  ColorEntry(QColor( 178,  24,  24),  0, 0),  
    ColorEntry(QColor( 24, 178,  24),  0, 0),  ColorEntry(QColor( 178, 104,  24),  0, 0),  
    ColorEntry(QColor( 24,  24, 178),  0, 0),  ColorEntry(QColor( 178,  24, 178),  0, 0),  
    ColorEntry(QColor( 24, 178, 178),  0, 0),  ColorEntry(QColor( 178, 178, 178),  0, 0),  
    ColorEntry(QColor(  0,   0,   0),  0, 1),  ColorEntry(QColor( 255, 255, 221),  1, 0),  
    ColorEntry(QColor(104, 104, 104),  0, 0),  ColorEntry(QColor( 255,  84,  84),  0, 0),  
    ColorEntry(QColor( 84, 255,  84),  0, 0),  ColorEntry(QColor( 255, 255,  84),  0, 0),  
    ColorEntry(QColor( 84,  84, 255),  0, 0),  ColorEntry(QColor( 255,  84, 255),  0, 0),  
    ColorEntry(QColor( 84, 255, 255),  0, 0),  ColorEntry(QColor( 255, 255, 255),  0, 0)
};
 			  
			  
			  


#endif

