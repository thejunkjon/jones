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
#include <boost/core/ignore_unused.hpp>
#include <memory.hh>

#include "apu.hh"
#include "cpu.hh"
#include "nes.hh"
#include "nes_rom.hh"
#include "ppu.hh"

using namespace jones;

template <typename C>
class memory_mappable_component : public memory_mappable {
public:
  memory_mappable_component(C &component, uint16_t start_address, uint16_t end_address)
      : component_(component), start_address_(start_address), end_address_(end_address) {}

  uint16_t start_address() override {
    return start_address_;
  }

  uint16_t end_address() override {
    return end_address_;
  }

  uint8_t read(const uint16_t address) override {
    return component_.read(address);
  }

  void write(const uint16_t address, const uint8_t data) override {
    component_.write(address, data);
  }

private:
  C &component_;
  const uint16_t start_address_;
  const uint32_t end_address_;
};

class nes::nes_impl {
public:
  nes_impl() : memory_(), apu_(memory_), cpu_(memory_), ppu_(memory_) {
    memory_.map(std::make_unique<memory_mappable_component<cpu>>(cpu_, 0x0000, 0x1FFF));
    memory_.map(std::make_unique<memory_mappable_component<ppu>>(ppu_, 0x2000, 0x3FFF));
    memory_.map(std::make_unique<memory_mappable_component<apu>>(apu_, 0x4000, 0x4017));
    memory_.map(std::make_unique<memory_mappable_component<cpu>>(cpu_, 0x4000, 0x4017));
  }

  void load(const nes_rom &rom) {
    boost::ignore_unused(rom);
  }

  void run() {
  }

  void reset() {
  }

  void trace(const char *trace_file) {
    boost::ignore_unused(trace_file);
  }

private:
  memory memory_;
  apu apu_;
  cpu cpu_;
  ppu ppu_;
};

nes::nes() noexcept
    : pimpl_(std::make_unique<nes_impl>()) {
}

void nes::load(const nes_rom &rom) {
  pimpl_->load(rom);
}

void nes::run() {
  pimpl_->run();
}

void nes::reset() {
  pimpl_->reset();
}

void nes::trace(const char *trace_file) {
  pimpl_->trace(trace_file);
}