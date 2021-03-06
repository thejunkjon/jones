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
#include <cstring>
#include <iomanip>
#include <sstream>
#include <vector>

#include "configuration.hh"
#include "decode.hh"
#include "disassemble.hh"
#include "disassemble_internal.hh"
#include "instruction.hh"

namespace jdi = jones::disassemble;
namespace jde = jones::decode;
namespace jco = jones::configuration;

namespace {

auto use_absolute_addresses() -> bool {
  return jco::configuration::instance().get<bool>(jco::property::PROPERTY_DISASM_USE_ABSOLUTE_ADDRESSES, false);
}

auto disassemble_opcode(jde::instruction const &decoded_instruction) -> std::string {
  return instruction_set[decoded_instruction.decoded_opcode.value].mnemonic;
}

auto disassemble_operand_immediate(jde::operand const &decoded_operand) -> std::string {
  std::stringstream operand_string;
  const int immediate_value = std::get<uint8_t>(decoded_operand.value);
  operand_string << " #$" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << immediate_value;
  return operand_string.str();
}

auto disassemble_operand_memory(jde::operand const &decoded_operand, addressing_mode_type const addressing_mode) -> std::string {
  auto const operand_string_width = use_absolute_addresses() ? 4 : 2;
  std::stringstream operand_string;
  switch (addressing_mode) {
  case addressing_mode_type::ABSOLUTE: {
    const int memory_value = std::get<uint16_t>(decoded_operand.value);
    operand_string << " $" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << memory_value;
    break;
  }
  case addressing_mode_type::ABSOLUTE_X: {
    const int memory_value = std::get<uint16_t>(decoded_operand.value);
    operand_string << " $" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << memory_value << ",X";
    break;
  }
  case addressing_mode_type::ABSOLUTE_Y: {
    const int memory_value = std::get<uint16_t>(decoded_operand.value);
    operand_string << " $" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << memory_value << ",Y";
    break;
  }
  case addressing_mode_type::IMMEDIATE: {
    const int immediate_value = std::get<uint16_t>(decoded_operand.value);
    operand_string << " #" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << immediate_value;
    break;
  }
  case addressing_mode_type::INDEXED_INDIRECT: {
    const int memory_value = std::get<uint8_t>(decoded_operand.value);
    operand_string << " ($" << std::hex << std::uppercase << std::setw(operand_string_width) << std::setfill('0') << memory_value << ",X)";
    break;
  }
  case addressing_mode_type::INDIRECT_INDEXED: {
    const int memory_value = std::get<uint8_t>(decoded_operand.value);
    operand_string << " ($" << std::hex << std::uppercase << std::setw(operand_string_width) << std::setfill('0') << memory_value << "),Y";
    break;
  }
  case addressing_mode_type::INDIRECT: {
    const int memory_value = std::get<uint16_t>(decoded_operand.value);
    operand_string << " ($" << std::hex << std::uppercase << std::setw(4) << std::setfill('0') << memory_value << ")";
    break;
  }
  case addressing_mode_type::RELATIVE: {
    const int memory_value = std::get<uint8_t>(decoded_operand.value);
    operand_string << " $" << std::hex << std::uppercase << std::setw(operand_string_width) << std::setfill('0') << memory_value;
    break;
  }
  case addressing_mode_type::ZERO_PAGE: {
    const int memory_value = std::get<uint8_t>(decoded_operand.value);
    operand_string << " $" << std::hex << std::uppercase << std::setw(operand_string_width) << std::setfill('0') << memory_value;
    break;
  }
  case addressing_mode_type::ZERO_PAGE_X: {
    const int memory_value = std::get<uint8_t>(decoded_operand.value);
    operand_string << " $" << std::hex << std::uppercase << std::setw(operand_string_width) << std::setfill('0') << memory_value << ",X";
    break;
  }
  case addressing_mode_type::ZERO_PAGE_Y: {
    const int memory_value = std::get<uint8_t>(decoded_operand.value);
    operand_string << " $" << std::hex << std::uppercase << std::setw(operand_string_width) << std::setfill('0') << memory_value << ",Y";
    break;
  }
  default: {
    operand_string << "";
    break;
  }
  }
  return operand_string.str();
}

auto disassemble_operand_register(jde::operand const &decoded_operand, addressing_mode_type const addressing_mode) -> std::string {
  boost::ignore_unused(decoded_operand);
  std::stringstream operand_string;
  switch (addressing_mode) {
  case addressing_mode_type::ACCUMULATOR: {
    operand_string << " A";
    break;
  }
  default: {
    operand_string << "";
    break;
  }
  }
  return operand_string.str();
}

auto disassemble_operand(jde::instruction const &decoded_instruction) -> std::string {
  auto const &decoded_addressing_mode = decoded_instruction.decoded_addressing_mode;
  auto const &decoded_operand = decoded_instruction.decoded_operand;
  switch (decoded_operand.type) {
  case operand_type::IMMEDIATE:
    return disassemble_operand_immediate(decoded_operand);
  case operand_type::MEMORY:
    return disassemble_operand_memory(decoded_operand, decoded_addressing_mode);
  case operand_type::REGISTER:
    return disassemble_operand_register(decoded_operand, decoded_addressing_mode);
  case operand_type::NONE:
    return std::string("");
  default:
    return "";
  }
}

} // namespace

auto disassemble::disassemble(uint8_t *const buffer, size_t const length_in_bytes, disassemble::disassemble_listener_ptr const listener) -> disassemble::instructions {
  std::vector<jdi::instruction> disassembled_instructions;
  int buffer_offset = 0;
  auto decoded_instruction = jde::decode(buffer, length_in_bytes);

  if (listener != nullptr) {
    listener->on_decoded(decoded_instruction);
  }

  while (jde::is_valid(decoded_instruction)) {
    auto const opcode_string = disassemble_opcode(decoded_instruction);
    auto const operand_string = disassemble_operand(decoded_instruction);

    jdi::instruction disassembled_instruction = jdi::instruction();
    disassembled_instruction.address = buffer_offset;
    disassembled_instruction.length_in_bytes = decoded_instruction.encoded_length_in_bytes;
    disassembled_instruction.binary = decoded_instruction.encoded;
    disassembled_instruction.opcode = opcode_string;
    disassembled_instruction.operand = operand_string;

    if (listener != nullptr) {
      listener->on_disassembled(disassembled_instruction);
    }

    disassembled_instructions.push_back(disassembled_instruction);

    buffer_offset += decoded_instruction.encoded_length_in_bytes;
    decoded_instruction = jde::decode(buffer + buffer_offset, length_in_bytes - buffer_offset);
  }
  return jdi::instructions{disassembled_instructions, 0};
}

auto disassemble::disassemble(uint8_t *const buffer, size_t const length_in_bytes) -> disassemble::instructions {
  return disassemble(buffer, length_in_bytes, nullptr);
}
