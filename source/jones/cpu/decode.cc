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
#include <boost/assert.hpp>
#include <cstring>

#include "decode.hh"
#include "log.hh"

using namespace jones;

namespace {

decode::instruction create_empty_instruction(decode::result const result) {
  return decode::instruction{
      .encoded = {},
      .encoded_length_in_bytes = 0,
      .decoded_result = result,
      .decoded_opcode = {opcode_type::INVALID, 0},
      .decoded_operand = {operand_type::INVALID, static_cast<uint8_t>(0)},
      .decoded_addressing_mode = addressing_mode_type::INVALID};
}

} // namespace

auto decode::decode(uint8_t *const buffer, size_t const length_in_bytes) -> decode::instruction {
  if (length_in_bytes < 1) {
    //
    // buffer is not sufficient size to hold an instruction
    //
    return create_empty_instruction(result::ERROR_INVALID);
  }
  auto const opcode = buffer[0];
  auto const instruction = instruction_set[opcode];
  if (length_in_bytes < instruction.length) {
    //
    // buffer is smaller than expected size
    //
    return create_empty_instruction(
        instruction.length == 1 ? result::ERROR_REQUIRES_ONE_BYTE : instruction.length == 2 ? result::ERROR_REQUIRES_TWO_BYTES : instruction.length == 3 ? result::ERROR_REQUIRES_THREE_BYTES : result::ERROR_INVALID);
  }
  auto const instruction_length = instruction.length;
  decode::instruction decoded_instruction = create_empty_instruction(result::SUCCESS);
  std::memcpy(decoded_instruction.encoded.data(), buffer, instruction_length);
  decoded_instruction.encoded_length_in_bytes = instruction_length;
  decoded_instruction.decoded_addressing_mode = instruction.addressing_mode;
  decoded_instruction.decoded_opcode = {instruction.opcode, opcode};

  switch (instruction.addressing_mode) {
  case addressing_mode_type::ABSOLUTE:
  case addressing_mode_type::ABSOLUTE_X:
  case addressing_mode_type::ABSOLUTE_Y:
    decoded_instruction.decoded_operand = {operand_type::MEMORY, static_cast<uint16_t>(buffer[1] | (buffer[2] << 8))};
    break;
  case addressing_mode_type::ACCUMULATOR:
    decoded_instruction.decoded_operand = {operand_type::REGISTER, static_cast<uint8_t>(0x00)};
    break;
  case addressing_mode_type::IMMEDIATE:
    decoded_instruction.decoded_operand = {operand_type::IMMEDIATE, buffer[1]};
    break;
  case addressing_mode_type::IMPLICIT:
    decoded_instruction.decoded_operand = {operand_type::NONE, static_cast<uint8_t>(0x00)};
    break;
  case addressing_mode_type::INDIRECT:
    decoded_instruction.decoded_operand = {operand_type::MEMORY, static_cast<uint16_t>(buffer[1] | (buffer[2] << 8))};
    break;
  case addressing_mode_type::INDEXED_INDIRECT:
  case addressing_mode_type::INDIRECT_INDEXED:
    decoded_instruction.decoded_operand = {operand_type::MEMORY, static_cast<uint8_t>(buffer[1])};
    break;
  case addressing_mode_type::RELATIVE:
    decoded_instruction.decoded_operand = {operand_type::MEMORY, static_cast<uint8_t>(buffer[1])};
    break;
  case addressing_mode_type::ZERO_PAGE:
  case addressing_mode_type::ZERO_PAGE_X:
  case addressing_mode_type::ZERO_PAGE_Y:
    decoded_instruction.decoded_operand = {operand_type::MEMORY, static_cast<uint8_t>(buffer[1])};
    break;
  case addressing_mode_type::INVALID:
    LOG_ERROR << "invalid addressing mode type found";
    decoded_instruction.decoded_result = result::ERROR_INVALID;
    break;
  }

  BOOST_ASSERT(instruction.addressing_mode != addressing_mode_type::INVALID);

  return decoded_instruction;
}

auto decode::is_valid(decode::instruction const &decoded_instruction) -> bool {
  return !(decoded_instruction.decoded_opcode.type == opcode_type::INVALID) &&
         !(decoded_instruction.decoded_operand.type == operand_type::INVALID);
}
