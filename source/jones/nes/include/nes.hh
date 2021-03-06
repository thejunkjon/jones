//
// MIT License
//
// Copyright 2017-2018
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
#ifndef JONES_NES_NES_HH
#define JONES_NES_NES_HH

#include "controller.hh"
#include "screen.hh"

#include <memory>

namespace jones {

class nes final {
public:
  explicit nes(const char *rom_path) noexcept;

  ~nes();

  auto power() -> bool;

  auto reset() -> bool;

  auto run(size_t step_limit = 0) -> void;

  auto stop() -> void;

  auto controller_one() -> controller::controller_ptr;

  auto controller_two() -> controller::controller_ptr;

  auto attach_screen(std::unique_ptr<screen::screen> screen = nullptr) -> void;

private:
  friend class debugger;

  class impl;

  std::unique_ptr<impl> pimpl_;
};

} // namespace jones

#endif // JONES_NES_NES_HH
