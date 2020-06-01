/** @file
  Narrow font Data definition for GraphicsConsole driver.

Copyright (c) 2006 - 2008, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "GraphicsConsole.h"



EFI_NARROW_GLYPH  gUsStdNarrowGlyphData[] = {
  //
  // Unicode glyphs from 0x20 to 0x7e are the same as ASCII characters 0x20 to 0x7e
  //
 

  { (CHAR16)BOXDRAW_HORIZONTAL,                 0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_VERTICAL,                   0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_DOWN_RIGHT,                 0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_DOWN_LEFT,                  0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_UP_RIGHT,                   0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_UP_LEFT,                    0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_VERTICAL_RIGHT,             0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_VERTICAL_LEFT,              0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xF8,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_DOWN_HORIZONTAL,            0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_UP_HORIZONTAL,              0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_VERTICAL_HORIZONTAL,        0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_DOUBLE_HORIZONTAL,          0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_DOUBLE_VERTICAL,            0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},
  { (CHAR16)BOXDRAW_DOWN_RIGHT_DOUBLE,          0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x18,0x1F,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_DOWN_DOUBLE_RIGHT,          0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},
  { (CHAR16)BOXDRAW_DOUBLE_DOWN_RIGHT,          0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x30,0x37,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},
  { (CHAR16)BOXDRAW_DOWN_LEFT_DOUBLE,           0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x18,0xF8,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_DOWN_DOUBLE_LEFT,           0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},
  { (CHAR16)BOXDRAW_DOUBLE_DOWN_LEFT,           0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x06,0xF6,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},
  { (CHAR16)BOXDRAW_UP_RIGHT_DOUBLE,            0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0x18,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_UP_DOUBLE_RIGHT,            0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_DOUBLE_UP_RIGHT,            0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x37,0x30,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_UP_LEFT_DOUBLE,             0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xF8,0x18,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_UP_DOUBLE_LEFT,             0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_DOUBLE_UP_LEFT,             0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0xF6,0x06,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_VERTICAL_RIGHT_DOUBLE,      0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0x18,0x1F,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_VERTICAL_DOUBLE_RIGHT,      0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x37,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},
  { (CHAR16)BOXDRAW_DOUBLE_VERTICAL_RIGHT,      0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x37,0x30,0x37,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},
  { (CHAR16)BOXDRAW_VERTICAL_LEFT_DOUBLE,       0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xF8,0x18,0xF8,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_VERTICAL_DOUBLE_LEFT,       0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0xF6,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},
  { (CHAR16)BOXDRAW_DOUBLE_VERTICAL_LEFT,       0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0xF6,0x06,0xF6,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},
  { (CHAR16)BOXDRAW_DOWN_HORIZONTAL_DOUBLE,     0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_DOWN_DOUBLE_HORIZONTAL,     0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},
  { (CHAR16)BOXDRAW_DOUBLE_DOWN_HORIZONTAL,     0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0xF7,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},
  { (CHAR16)BOXDRAW_UP_HORIZONTAL_DOUBLE,       0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xFF,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_UP_DOUBLE_HORIZONTAL,       0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_DOUBLE_UP_HORIZONTAL,       0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0xF7,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE, 0x00, {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xFF,0x18,0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18}},
  { (CHAR16)BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL, 0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0xFF,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},
  { (CHAR16)BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL, 0x00, {0x36,0x36,0x36,0x36,0x36,0x36,0x36,0xF7,0x00,0xF7,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36}},

  { (CHAR16)BLOCKELEMENT_FULL_BLOCK,            0x00, {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}},
  { (CHAR16)BLOCKELEMENT_LIGHT_SHADE,           0x00, {0x22,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0x22}},

  { (CHAR16)GEOMETRICSHAPE_RIGHT_TRIANGLE,      0x00, {0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xF0,0xF8,0xFE,0xF8,0xF0,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)GEOMETRICSHAPE_LEFT_TRIANGLE,       0x00, {0x00,0x00,0x00,0x00,0x00,0x06,0x0E,0x1E,0x3E,0xFE,0x3E,0x1E,0x0E,0x06,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)GEOMETRICSHAPE_UP_TRIANGLE,         0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x38,0x38,0x7C,0x7C,0xFE,0xFE,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)GEOMETRICSHAPE_DOWN_TRIANGLE,       0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFE,0x7C,0x7C,0x38,0x38,0x10,0x00,0x00,0x00,0x00,0x00,0x00}},

  { (CHAR16)ARROW_UP,                           0x00, {0x00,0x00,0x00,0x18,0x3C,0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)ARROW_DOWN,                         0x00, {0x00,0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7E,0x3C,0x18,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)ARROW_LEFT,                         0x00, {0x00,0x00,0x00,0x00,0x00,0x20,0x60,0x60,0xFE,0xFE,0x60,0x60,0x20,0x00,0x00,0x00,0x00,0x00,0x00}},
  { (CHAR16)ARROW_RIGHT,                        0x00, {0x00,0x00,0x00,0x00,0x00,0x08,0x0C,0x0C,0xFE,0xFE,0x0C,0x0C,0x08,0x00,0x00,0x00,0x00,0x00,0x00}},

  { 0x0000, 0x00, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} //EOL
};

// Get available Unicode glyphs narrow fonts(8*19 pixels) size.
UINT32 mNarrowFontSize =  sizeof (gUsStdNarrowGlyphData);
