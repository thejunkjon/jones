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
#ifndef JONES_PPU_PPU_HH
#define JONES_PPU_PPU_HH

#include <memory>

#include "cpu.hh"
#include "memory.hh"
#include "screen.hh"

namespace jones::ppu {

struct ppu_state {

  size_t cycle;

  size_t scanline;

  size_t frame;
};

class ppu : public memory_component {
public:
  ppu(memory &cpu_memory, memory &ppu_memory, cpu &cpu, screen::screen *screen);

  ~ppu() override;

  auto initialize() -> void;

  auto uninitialize() -> void;

  auto peek(uint16_t address) const -> uint8_t override;

  auto read(uint16_t address) const -> uint8_t override;

  auto write(uint16_t address, uint8_t data) -> void override;

  auto step() -> uint8_t;

  auto get_state() const -> ppu_state;

  auto set_state(const ppu_state &state) -> void;

private:
  class impl;

  std::unique_ptr<impl> impl_;
};

} // namespace jones::ppu

#endif // JONES_PPU_PPU_HH
