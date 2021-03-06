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
#ifndef JONES_PPU_NAME_TABLE_HH
#define JONES_PPU_NAME_TABLE_HH

#include <array>
#include <cstdint>

namespace jones::ppu {

constexpr uint16_t name_table_memory_begin = 0x2000;

constexpr uint16_t name_table_memory_end = 0x3EFF;

constexpr uint16_t name_table_size = 0x400;

constexpr uint16_t name_table_max_size = 0x1000;

constexpr uint16_t attribute_table_memory_begin = 0x23C0;

class name_table {
public:
  auto peek(uint16_t address) const -> uint8_t;

  auto read(uint16_t address) const -> uint8_t;

  auto write(uint16_t address, uint8_t data) -> void;

private:
  std::array<uint8_t, name_table_size * 2> name_table_{};
};

} // namespace jones::ppu

#endif // JONES_PPU_NAME_TABLE_HH
