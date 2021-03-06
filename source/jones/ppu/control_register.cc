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
#include <boost/static_assert.hpp>

#include "control_register.hh"

using namespace jones::ppu;

namespace {

auto flag_to_position(control_flag const flag) -> auto {
  switch (flag) {
  case control_flag::NAME_TABLE_ONE:
    return 0;
  case control_flag::NAME_TABLE_TWO:
    return 1;
  case control_flag::VRAM_INCREMENT:
    return 2;
  case control_flag::SPRITE_TABLE:
    return 3;
  case control_flag::BACKGROUND_TABLE:
    return 4;
  case control_flag::SPRITE_SIZE:
    return 5;
  case control_flag::MASTER_SLAVE:
    return 6;
  case control_flag::GENERATE_NMI_ON_VBLANK:
    return 7;
  default:
    BOOST_STATIC_ASSERT("unexpected flag for control register");
    return -1;
  }
}

} // namespace

control_register::control_register(uint8_t const flags) {
  set(flags);
}

auto control_register::is_set(control_flag const flag) const -> bool {
  return control_flags_.test(flag_to_position(flag));
}

auto control_register::set(control_flag const flag) -> uint8_t {
  control_flags_.set(flag_to_position(flag), true);
  return get();
}

auto control_register::clear(control_flag const flag) -> uint8_t {
  control_flags_.set(flag_to_position(flag), false);
  return get();
}

auto control_register::set(uint8_t const flags) -> uint8_t {
  (0x01U & flags) ? set(control_flag::NAME_TABLE_ONE) : clear(control_flag::NAME_TABLE_ONE);
  (0x02U & flags) ? set(control_flag::NAME_TABLE_TWO) : clear(control_flag::NAME_TABLE_TWO);
  (0x04U & flags) ? set(control_flag::VRAM_INCREMENT) : clear(control_flag::VRAM_INCREMENT);
  (0x08U & flags) ? set(control_flag::SPRITE_TABLE) : clear(control_flag::SPRITE_TABLE);
  (0x10U & flags) ? set(control_flag::BACKGROUND_TABLE) : clear(control_flag::BACKGROUND_TABLE);
  (0x20U & flags) ? set(control_flag::SPRITE_SIZE) : clear(control_flag::SPRITE_SIZE);
  (0x40U & flags) ? set(control_flag::MASTER_SLAVE) : clear(control_flag::MASTER_SLAVE);
  (0x80U & flags) ? set(control_flag::GENERATE_NMI_ON_VBLANK) : clear(control_flag::GENERATE_NMI_ON_VBLANK);
  return get();
}

auto control_register::get() const -> uint8_t {
  return (is_set(control_flag::NAME_TABLE_ONE) ? 0x01U : 0x00U) |
         (is_set(control_flag::NAME_TABLE_TWO) ? 0x02U : 0x00U) |
         (is_set(control_flag::VRAM_INCREMENT) ? 0x04U : 0x00U) |
         (is_set(control_flag::SPRITE_TABLE) ? 0x08U : 0x00U) |
         (is_set(control_flag::BACKGROUND_TABLE) ? 0x10U : 0x00U) |
         (is_set(control_flag::SPRITE_SIZE) ? 0x20U : 0x00U) |
         (is_set(control_flag::MASTER_SLAVE) ? 0x40U : 0x00U) |
         (is_set(control_flag::GENERATE_NMI_ON_VBLANK) ? 0x80U : 0x00U);
}
