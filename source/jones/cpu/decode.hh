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
#ifndef JONES_CPU_DECODE_HH
#define JONES_CPU_DECODE_HH

#include <array>
#include <cstdint>
#include <stddef.h>
#include <variant>

#include "instruction.hh"
#include "operand.hh"

using namespace jones;

namespace jones::decode {

constexpr unsigned int max_length_in_bytes = 3;

enum class result {
  SUCCESS,

  ERROR_INVALID,

  ERROR_REQUIRES_ONE_BYTE,

  ERROR_REQUIRES_TWO_BYTES,

  ERROR_REQUIRES_THREE_BYTES,
};

struct opcode {
  opcode_type type;
  uint8_t value;
};

struct operand {
  operand_type type;
  std::variant<uint8_t, uint16_t> value;
};

struct instruction {
  std::array<uint8_t, max_length_in_bytes> encoded;
  uint8_t encoded_length_in_bytes;

  result decoded_result;

  opcode decoded_opcode;
  operand decoded_operand;

  addressing_mode_type decoded_addressing_mode;
};

instruction decode(uint8_t *buffer, size_t length_in_bytes);

bool is_valid(const instruction &decoded_instruction);

} // namespace jones::decode

#endif // JONES_CPU_DECODE_HH
