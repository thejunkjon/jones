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
#ifndef JONES_PPU_PATTERN_TABLE_HH
#define JONES_PPU_PATTERN_TABLE_HH

#include "memory.hh"

#include <cstdint>

namespace jones::ppu {

constexpr auto pattern_table_memory_begin = 0x0000;

constexpr auto pattern_table_memory_end = 0x1FFF;

constexpr auto pattern_table_zero_memory_begin = 0x0000;

constexpr auto pattern_table_one_memory_begin = 0x1000;

class pattern_table : public memory_component {
public:
  auto peek(uint16_t address) const -> uint8_t override;

  auto read(uint16_t address) const -> uint8_t override;

  auto write(uint16_t address, uint8_t data) -> void override;
};

} // namespace jones::ppu

#endif // JONES_PPU_PATTERN_TABLE_HH
