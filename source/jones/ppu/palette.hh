//
// MIT License
//
// Copyright 2019
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#ifndef JONES_PPU_PALETTE_HH
#define JONES_PPU_PALETTE_HH

#include <cstdint>

namespace jones::ppu {

// ----------------------------------------------------------------------------
//
// Memory layout for Palette is documented here:
//
// https://wiki.nesdev.com/w/index.php/PPU_palettes
//
// ----------------------------------------------------------------------------
// Address Range  |  Size   | Purpose
// ----------------------------------------------------------------------------
// $3F00-$3F00    |  $0001  | Universal Background Color
// ----------------------------------------------------------------------------
// $3F01-$3F03    |  $0002  | Background Palette #0
// $3F05-$3F07    |  $0002  | Background Palette #1
// $3F09-$3F0B    |  $0002  | Background Palette #2
// $3F0D-$3F0F    |  $0002  | Background Palette #3
// ----------------------------------------------------------------------------
// $3F11-$3F13    |  $0002  | Sprite Palette #0
// $3F15-$3F17    |  $0002  | Sprite Palette #1
// $3F19-$3F1B    |  $0002  | Sprite Palette #2
// $3F1D-$3F1F    |  $0002  | Sprite Palette #3
// ----------------------------------------------------------------------------
//
class palette {
public:
  palette() = default;

  ~palette() = default;

  auto read(uint16_t address) const -> uint8_t;

  auto write(uint16_t address, uint8_t data) -> void;
};

} // namespace jones::ppu

#endif // JONES_PPU_PALETTE_HH