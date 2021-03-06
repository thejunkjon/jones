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
#ifndef JONES_CPU_DISASSEMBLE_INTERNAL_HH
#define JONES_CPU_DISASSEMBLE_INTERNAL_HH

#include <cstdint>
#include <memory>

#include "decode.hh"
#include "disassemble.hh"

namespace jones::disassemble {

class disassemble_listener {
public:
  virtual ~disassemble_listener() = default;

  virtual void on_decoded(decode::instruction &instruction) = 0;

  virtual void on_disassembled(disassemble::instruction &instruction) = 0;
};

using disassemble_listener_ptr = std::unique_ptr<disassemble_listener>;

disassemble::instructions disassemble(uint8_t *buffer, size_t length_in_bytes, disassemble_listener_ptr listener);

} // namespace jones::disassemble

#endif // JONES_CPU_DISASSEMBLE_INTERNAL_HH
