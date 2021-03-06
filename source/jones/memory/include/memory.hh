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
#ifndef JONES_MEMORY_MEMORY_HH
#define JONES_MEMORY_MEMORY_HH

#include <cstdint>
#include <memory>
#include <vector>

namespace jones {

// ----------------------------------------------------------------------------
//
// Memory layout for NES CPU is documented here:
//
// https://wiki.nesdev.com/w/index.php/CPU_memory_map
//
// ----------------------------------------------------------------------------
// Address Range  |  Size   | Device
// ----------------------------------------------------------------------------
// $0000-$07FF    |  $0800  | Internal RAM
// $0800-$0FFF    |  $0800  | Mirrors of Internal RAM ($0000-$07FF)
// $1000-$17FF    |  $0800  | Mirrors of Internal RAM ($0000-$07FF)
// $1800-$1FFF    |  $0800  | Mirrors of Internal RAM ($0000-$07FF)
// ----------------------------------------------------------------------------
// $2000-$2007    |  $0008  | Mapped to PPU registers.
// $2008-$3FFF    |  $1FF8  | Mirrors of $2000-2007 (Repeats every 8 bytes).
// $4000-$4017	  |  $0018  | Mapped to APU and I/O registers.
// $4018-$401F	  |  $0008  | Mapped to APU and I/O functionality (disabled).
// $4020-$FFFF    |  $BFE0  | Mapped to Cartridge.
// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
//
// Memory layout for NES PPU is documented here:
//
// https://wiki.nesdev.com/w/index.php/PPU_memory_map
//
// ----------------------------------------------------------------------------
// Address Range  |  Size   | Device
// ----------------------------------------------------------------------------
// $0000-$0FFF    |  $1000  | Pattern Table #0
// $1000-$1FFF    |  $1000  | Pattern Table #1
// ----------------------------------------------------------------------------
// $2000-$23FF    |  $0400  | Name Table #0
// $2400-$27FF    |  $0400  | Name Table #1
// $2800-$2BFF    |  $0400  | Name Table #2
// $2C00-$2FFF    |  $0400  | Name Table #3
// ----------------------------------------------------------------------------
// $3000-$3EFF    |  $0F00  | Mirrors of $2000-$2FFF
// $3F00-$3F1F    |  $0020  | Palette RAM indexes
// $3F20-$3FFF    |  $00E0  | Mirrors of $3F00-$3F1F
// ----------------------------------------------------------------------------
//
class memory_component {
public:
  memory_component() = default;

  virtual ~memory_component() = default;

  virtual auto peek(uint16_t address) const -> uint8_t = 0;

  virtual auto read(uint16_t address) const -> uint8_t = 0;

  virtual auto write(uint16_t address, uint8_t data) -> void = 0;
};

class memory_mappable : public memory_component {
public:
  memory_mappable() = default;

  ~memory_mappable() override = default;

  virtual auto start_address() const -> uint16_t = 0;

  virtual auto end_address() const -> uint16_t = 0;

  virtual auto tag() const -> const char * = 0;
};

template <typename C>
class memory_mappable_component : public memory_mappable {
public:
  memory_mappable_component(C *const component, const char *tag, uint16_t const start_address, uint16_t const end_address)
      : component_(component), tag_(tag), start_address_(start_address), end_address_(end_address) {
    //
    // nothing to do.
    //
  }

  auto start_address() const -> uint16_t override {
    return start_address_;
  }

  auto end_address() const -> uint16_t override {
    return end_address_;
  }

  auto peek(uint16_t const address) const -> uint8_t override {
    return component_->peek(address);
  }

  auto read(uint16_t const address) const -> uint8_t override {
    return component_->read(address);
  }

  auto write(uint16_t const address, uint8_t const data) -> void override {
    component_->write(address, data);
  }

  auto tag() const -> const char * override {
    return tag_;
  }

private:
  C *const component_;

  const char *const tag_;

  const uint16_t start_address_;

  const uint32_t end_address_;
};

using memory_mappable_ptr = std::unique_ptr<memory_mappable>;

class memory {
public:
  explicit memory(const char *const tag) : tag_(tag) {
    //
    // nothing to do.
    //
  }

  ~memory() = default;

  auto peek(uint16_t address) const -> uint8_t;

  auto peek_word(uint16_t address) const -> uint16_t;

  auto read(uint16_t address) const -> uint8_t;

  auto read_word(uint16_t address) const -> uint16_t;

  auto write(uint16_t address, uint8_t data) const -> void;

  auto map(memory_mappable_ptr mappable) -> void;

  auto print(std::ostream &out) const -> void;

private:
  char const *const tag_;

  std::vector<memory_mappable_ptr> memory_mappings_;
};

} // namespace jones

#endif // JONES_MEMORY_MEMORY_HH
