//
// MIT License
//
// Copyright 2018-2019
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
#include "instruction.hh"

namespace jones {

using op = opcode_type;
using am = addressing_mode_type;

//
// Reference: https://wiki.nesdev.com/w/index.php/CPU_unofficial_opcodes
//
struct instruction instruction_set[256]{

    {0x00, op::BRK, "BRK", 1, am::IMPLICIT},
    {0x01, op::ORA, "ORA", 2, am::INDEXED_INDIRECT},
    {0x02, op::STP, "STP", 1, am::IMPLICIT},
    {0x03, op::SLO, "SLO", 2, am::INDEXED_INDIRECT},
    {0x04, op::NOP, "NOP", 2, am::ZERO_PAGE},
    {0x05, op::ORA, "ORA", 2, am::ZERO_PAGE},
    {0x06, op::ASL, "ASL", 2, am::ZERO_PAGE},
    {0x07, op::SLO, "SLO", 2, am::ZERO_PAGE},
    {0x08, op::PHP, "PHP", 1, am::IMPLICIT},
    {0x09, op::ORA, "ORA", 2, am::IMMEDIATE},
    {0x0A, op::ASL, "ASL", 1, am::ACCUMULATOR},
    {0x0B, op::ANC, "ANC", 2, am::IMMEDIATE},
    {0x0C, op::NOP, "NOP", 3, am::ABSOLUTE},
    {0x0D, op::ORA, "ORA", 3, am::ABSOLUTE},
    {0x0E, op::ASL, "ASL", 3, am::ABSOLUTE},
    {0x0F, op::SLO, "SLO", 3, am::ABSOLUTE},

    {0x10, op::BPL, "BPL", 2, am::RELATIVE},
    {0x11, op::ORA, "ORA", 2, am::INDIRECT_INDEXED},
    {0x12, op::STP, "STP", 1, am::IMPLICIT},
    {0x13, op::SLO, "SLO", 2, am::INDIRECT_INDEXED},
    {0x14, op::NOP, "NOP", 2, am::ZERO_PAGE_X},
    {0x15, op::ORA, "ORA", 2, am::ZERO_PAGE_X},
    {0x16, op::ASL, "ASL", 2, am::ZERO_PAGE_X},
    {0x17, op::SLO, "SLO", 2, am::ZERO_PAGE_X},
    {0x18, op::CLC, "CLC", 1, am::IMPLICIT},
    {0x19, op::ORA, "ORA", 3, am::ABSOLUTE_Y},
    {0x1A, op::NOP, "NOP", 1, am::IMPLICIT},
    {0x1B, op::SLO, "SLO", 3, am::ABSOLUTE_Y},
    {0x1C, op::NOP, "NOP", 3, am::ABSOLUTE_X},
    {0x1D, op::ORA, "ORA", 3, am::ABSOLUTE_X},
    {0x1E, op::ASL, "ASL", 3, am::ABSOLUTE_X},
    {0x1F, op::SLO, "SLO", 3, am::ABSOLUTE_X},

    {0x20, op::JSR, "JSR", 3, am::ABSOLUTE},
    {0x21, op::AND, "AND", 2, am::INDEXED_INDIRECT},
    {0x22, op::STP, "STP", 1, am::IMPLICIT},
    {0x23, op::RLA, "RLA", 2, am::INDEXED_INDIRECT},
    {0x24, op::BIT, "BIT", 2, am::ZERO_PAGE},
    {0x25, op::AND, "AND", 2, am::ZERO_PAGE},
    {0x26, op::ROL, "ROL", 2, am::ZERO_PAGE},
    {0x27, op::RLA, "RLA", 2, am::ZERO_PAGE},
    {0x28, op::PLP, "PLP", 1, am::IMPLICIT},
    {0x29, op::AND, "AND", 2, am::IMMEDIATE},
    {0x2A, op::ROL, "ROL", 1, am::ACCUMULATOR},
    {0x2B, op::ANC, "ANC", 2, am::IMMEDIATE},
    {0x2C, op::BIT, "BIT", 3, am::ABSOLUTE},
    {0x2D, op::AND, "AND", 3, am::ABSOLUTE},
    {0x2E, op::ROL, "ROL", 3, am::ABSOLUTE},
    {0x2F, op::RLA, "RLA", 3, am::ABSOLUTE},

    {0x30, op::BMI, "BMI", 2, am::RELATIVE},
    {0x31, op::AND, "AND", 2, am::INDIRECT_INDEXED},
    {0x32, op::STP, "STP", 1, am::IMPLICIT},
    {0x33, op::RLA, "RLA", 2, am::INDIRECT_INDEXED},
    {0x34, op::NOP, "NOP", 2, am::ZERO_PAGE_X},
    {0x35, op::AND, "AND", 2, am::ZERO_PAGE_X},
    {0x36, op::ROL, "ROL", 2, am::ZERO_PAGE_X},
    {0x37, op::RLA, "RLA", 2, am::ZERO_PAGE_X},
    {0x38, op::SEC, "SEC", 1, am::IMPLICIT},
    {0x39, op::AND, "AND", 3, am::ABSOLUTE_Y},
    {0x3A, op::NOP, "NOP", 1, am::IMPLICIT},
    {0x3B, op::RLA, "RLA", 3, am::ABSOLUTE_Y},
    {0x3C, op::NOP, "NOP", 3, am::ABSOLUTE_X},
    {0x3D, op::AND, "AND", 3, am::ABSOLUTE_X},
    {0x3E, op::ROL, "ROL", 3, am::ABSOLUTE_X},
    {0x3F, op::RLA, "RLA", 3, am::ABSOLUTE_X},

    {0x40, op::RTI, "RTI", 1, am::IMPLICIT},
    {0x41, op::EOR, "EOR", 2, am::INDEXED_INDIRECT},
    {0x42, op::STP, "STP", 1, am::IMPLICIT},
    {0x43, op::SRE, "SRE", 2, am::INDEXED_INDIRECT},
    {0x44, op::NOP, "NOP", 2, am::ZERO_PAGE},
    {0x45, op::EOR, "EOR", 2, am::ZERO_PAGE},
    {0x46, op::LSR, "LSR", 2, am::ZERO_PAGE},
    {0x47, op::SRE, "SRE", 2, am::ZERO_PAGE},
    {0x48, op::PHA, "PHA", 1, am::IMPLICIT},
    {0x49, op::EOR, "EOR", 2, am::IMMEDIATE},
    {0x4A, op::LSR, "LSR", 1, am::ACCUMULATOR},
    {0x4B, op::ALR, "ALR", 2, am::IMMEDIATE},
    {0x4C, op::JMP, "JMP", 3, am::ABSOLUTE},
    {0x4D, op::EOR, "EOR", 3, am::ABSOLUTE},
    {0x4E, op::LSR, "LSR", 3, am::ABSOLUTE},
    {0x4F, op::SRE, "SRE", 3, am::ABSOLUTE},

    {0x50, op::BVC, "BVC", 2, am::RELATIVE},
    {0x51, op::EOR, "EOR", 2, am::INDIRECT_INDEXED},
    {0x52, op::STP, "STP", 1, am::IMPLICIT},
    {0x53, op::SRE, "SRE", 2, am::INDIRECT_INDEXED},
    {0x54, op::NOP, "NOP", 2, am::ZERO_PAGE_X},
    {0x55, op::EOR, "EOR", 2, am::ZERO_PAGE_X},
    {0x56, op::LSR, "LSR", 2, am::ZERO_PAGE_X},
    {0x57, op::SRE, "SRE", 2, am::ZERO_PAGE_X},
    {0x58, op::CLI, "CLI", 1, am::IMPLICIT},
    {0x59, op::EOR, "EOR", 3, am::ABSOLUTE_Y},
    {0x5A, op::NOP, "NOP", 1, am::IMPLICIT},
    {0x5B, op::SRE, "SRE", 3, am::ABSOLUTE_Y},
    {0x5C, op::NOP, "NOP", 3, am::ABSOLUTE_X},
    {0x5D, op::EOR, "EOR", 3, am::ABSOLUTE_X},
    {0x5E, op::LSR, "LSR", 3, am::ABSOLUTE_X},
    {0x5F, op::SRE, "SRE", 3, am::ABSOLUTE_X},

    {0x60, op::RTS, "RTS", 1, am::IMPLICIT},
    {0x61, op::ADC, "ADC", 2, am::INDEXED_INDIRECT},
    {0x62, op::STP, "STP", 1, am::IMPLICIT},
    {0x63, op::RRA, "RRA", 2, am::INDEXED_INDIRECT},
    {0x64, op::NOP, "NOP", 2, am::ZERO_PAGE},
    {0x65, op::ADC, "ADC", 2, am::ZERO_PAGE},
    {0x66, op::ROR, "ROR", 2, am::ZERO_PAGE},
    {0x67, op::RRA, "RRA", 2, am::ZERO_PAGE},
    {0x68, op::PLA, "PLA", 1, am::IMPLICIT},
    {0x69, op::ADC, "ADC", 2, am::IMMEDIATE},
    {0x6A, op::ROR, "ROR", 1, am::ACCUMULATOR},
    {0x6B, op::ARR, "ARR", 2, am::IMMEDIATE},
    {0x6C, op::JMP, "JMP", 3, am::INDIRECT},
    {0x6D, op::ADC, "ADC", 3, am::ABSOLUTE},
    {0x6E, op::ROR, "ROR", 3, am::ABSOLUTE},
    {0x6F, op::RRA, "RRA", 3, am::ABSOLUTE},

    {0x70, op::BVS, "BVS", 2, am::RELATIVE},
    {0x71, op::ADC, "ADC", 2, am::INDIRECT_INDEXED},
    {0x72, op::STP, "STP", 1, am::IMPLICIT},
    {0x73, op::RRA, "RRA", 2, am::INDIRECT_INDEXED},
    {0x74, op::NOP, "NOP", 2, am::ZERO_PAGE_X},
    {0x75, op::ADC, "ADC", 2, am::ZERO_PAGE_X},
    {0x76, op::ROR, "ROR", 2, am::ZERO_PAGE_X},
    {0x77, op::RRA, "RRA", 2, am::ZERO_PAGE_X},
    {0x78, op::SEI, "SEI", 1, am::IMPLICIT},
    {0x79, op::ADC, "ADC", 3, am::ABSOLUTE_Y},
    {0x7A, op::NOP, "NOP", 1, am::IMPLICIT},
    {0x7B, op::RRA, "RRA", 3, am::ABSOLUTE_Y},
    {0x7C, op::NOP, "NOP", 3, am::ABSOLUTE_X},
    {0x7D, op::ADC, "ADC", 3, am::ABSOLUTE_X},
    {0x7E, op::ROR, "ROR", 3, am::ABSOLUTE_X},
    {0x7F, op::RRA, "RRA", 3, am::ABSOLUTE_X},

    {0x80, op::NOP, "NOP", 2, am::IMMEDIATE},
    {0x81, op::STA, "STA", 2, am::INDEXED_INDIRECT},
    {0x82, op::NOP, "NOP", 2, am::IMMEDIATE},
    {0x83, op::SAX, "SAX", 2, am::INDEXED_INDIRECT},
    {0x84, op::STY, "STY", 2, am::ZERO_PAGE},
    {0x85, op::STA, "STA", 2, am::ZERO_PAGE},
    {0x86, op::STX, "STX", 2, am::ZERO_PAGE},
    {0x87, op::SAX, "SAX", 2, am::ZERO_PAGE},
    {0x88, op::DEY, "DEY", 1, am::IMPLICIT},
    {0x89, op::NOP, "NOP", 2, am::IMMEDIATE},
    {0x8A, op::TXA, "TXA", 1, am::IMPLICIT},
    {0x8B, op::XAA, "XAA", 2, am::IMMEDIATE},
    {0x8C, op::STY, "STY", 3, am::ABSOLUTE},
    {0x8D, op::STA, "STA", 3, am::ABSOLUTE},
    {0x8E, op::STX, "STX", 3, am::ABSOLUTE},
    {0x8F, op::SAX, "SAX", 3, am::ABSOLUTE},

    {0x90, op::BCC, "BCC", 2, am::RELATIVE},
    {0x91, op::STA, "STA", 2, am::INDIRECT_INDEXED},
    {0x92, op::STP, "STP", 1, am::IMPLICIT},
    {0x93, op::AHX, "AHX", 2, am::INDIRECT_INDEXED},
    {0x94, op::STY, "STY", 2, am::ZERO_PAGE_X},
    {0x95, op::STA, "STA", 2, am::ZERO_PAGE_X},
    {0x96, op::STX, "STX", 2, am::ZERO_PAGE_Y},
    {0x97, op::SAX, "SAX", 2, am::ZERO_PAGE_Y},
    {0x98, op::TYA, "TYA", 1, am::IMPLICIT},
    {0x99, op::STA, "STA", 3, am::ABSOLUTE_Y},
    {0x9A, op::TXS, "TXS", 1, am::IMPLICIT},
    {0x9B, op::TAS, "TAS", 3, am::ABSOLUTE_Y},
    {0x9C, op::SHY, "SHY", 3, am::ABSOLUTE_X},
    {0x9D, op::STA, "STA", 3, am::ABSOLUTE_X},
    {0x9E, op::SHX, "SHX", 3, am::ABSOLUTE_Y},
    {0x9F, op::AHX, "AHX", 3, am::ABSOLUTE_Y},

    {0xA0, op::LDY, "LDY", 2, am::IMMEDIATE},
    {0xA1, op::LDA, "LDA", 2, am::INDEXED_INDIRECT},
    {0xA2, op::LDX, "LDX", 2, am::IMMEDIATE},
    {0xA3, op::LAX, "LAX", 2, am::INDEXED_INDIRECT},
    {0xA4, op::LDY, "LDY", 2, am::ZERO_PAGE},
    {0xA5, op::LDA, "LDA", 2, am::ZERO_PAGE},
    {0xA6, op::LDX, "LDX", 2, am::ZERO_PAGE},
    {0xA7, op::LAX, "LAX", 2, am::ZERO_PAGE},
    {0xA8, op::TAY, "TAY", 1, am::IMPLICIT},
    {0xA9, op::LDA, "LDA", 2, am::IMMEDIATE},
    {0xAA, op::TAX, "TAX", 1, am::IMPLICIT},
    {0xAB, op::LAX, "LAX", 2, am::IMMEDIATE},
    {0xAC, op::LDY, "LDY", 3, am::ABSOLUTE},
    {0xAD, op::LDA, "LDA", 3, am::ABSOLUTE},
    {0xAE, op::LDX, "LDX", 3, am::ABSOLUTE},
    {0xAF, op::LAX, "LAX", 3, am::ABSOLUTE},

    {0xB0, op::BCS, "BCS", 2, am::RELATIVE},
    {0xB1, op::LDA, "LDA", 2, am::INDIRECT_INDEXED},
    {0xB2, op::STP, "STP", 1, am::IMPLICIT},
    {0xB3, op::LAX, "LAX", 2, am::INDIRECT_INDEXED},
    {0xB4, op::LDY, "LDY", 2, am::ZERO_PAGE_X},
    {0xB5, op::LDA, "LDA", 2, am::ZERO_PAGE_X},
    {0xB6, op::LDX, "LDX", 2, am::ZERO_PAGE_Y},
    {0xB7, op::LAX, "LAX", 2, am::ZERO_PAGE_Y},
    {0xB8, op::CLV, "CLV", 1, am::IMPLICIT},
    {0xB9, op::LDA, "LDA", 3, am::ABSOLUTE_Y},
    {0xBA, op::TSX, "TSX", 1, am::IMPLICIT},
    {0xBB, op::LAS, "LAS", 3, am::ABSOLUTE_Y},
    {0xBC, op::LDY, "LDY", 3, am::ABSOLUTE_X},
    {0xBD, op::LDA, "LDA", 3, am::ABSOLUTE_X},
    {0xBE, op::LDX, "LDX", 3, am::ABSOLUTE_Y},
    {0xBF, op::LAX, "LAX", 3, am::ABSOLUTE_Y},

    {0xC0, op::CPY, "CPY", 2, am::IMMEDIATE},
    {0xC1, op::CMP, "CMP", 2, am::INDEXED_INDIRECT},
    {0xC2, op::NOP, "NOP", 2, am::IMMEDIATE},
    {0xC3, op::DCP, "DCP", 2, am::INDEXED_INDIRECT},
    {0xC4, op::CPY, "CPY", 2, am::ZERO_PAGE},
    {0xC5, op::CMP, "CMP", 2, am::ZERO_PAGE},
    {0xC6, op::DEC, "DEC", 2, am::ZERO_PAGE},
    {0xC7, op::DCP, "DCP", 2, am::ZERO_PAGE},
    {0xC8, op::INY, "INY", 1, am::IMPLICIT},
    {0xC9, op::CMP, "CMP", 2, am::IMMEDIATE},
    {0xCA, op::DEX, "DEX", 1, am::IMPLICIT},
    {0xCB, op::AXS, "AXS", 2, am::IMMEDIATE},
    {0xCC, op::CPY, "CPY", 3, am::ABSOLUTE},
    {0xCD, op::CMP, "CMP", 3, am::ABSOLUTE},
    {0xCE, op::DEC, "DEC", 3, am::ABSOLUTE},
    {0xCF, op::DCP, "DCP", 3, am::ABSOLUTE},

    {0xD0, op::BNE, "BNE", 2, am::RELATIVE},
    {0xD1, op::CMP, "CMP", 2, am::INDIRECT_INDEXED},
    {0xD2, op::STP, "STP", 1, am::IMPLICIT},
    {0xD3, op::DCP, "DCP", 2, am::INDIRECT_INDEXED},
    {0xD4, op::NOP, "NOP", 2, am::ZERO_PAGE_X},
    {0xD5, op::CMP, "CMP", 2, am::ZERO_PAGE_X},
    {0xD6, op::DEC, "DEC", 2, am::ZERO_PAGE_X},
    {0xD7, op::DCP, "DCP", 2, am::ZERO_PAGE_X},
    {0xD8, op::CLD, "CLD", 1, am::IMPLICIT},
    {0xD9, op::CMP, "CMP", 3, am::ABSOLUTE_Y},
    {0xDA, op::NOP, "NOP", 1, am::IMPLICIT},
    {0xDB, op::DCP, "DCP", 3, am::ABSOLUTE_Y},
    {0xDC, op::NOP, "NOP", 3, am::ABSOLUTE_X},
    {0xDD, op::CMP, "CMP", 3, am::ABSOLUTE_X},
    {0xDE, op::DEC, "DEC", 3, am::ABSOLUTE_X},
    {0xDF, op::DCP, "DCP", 3, am::ABSOLUTE_X},

    {0xE0, op::CPX, "CPX", 2, am::IMMEDIATE},
    {0xE1, op::SBC, "SBC", 2, am::INDEXED_INDIRECT},
    {0xE2, op::NOP, "NOP", 2, am::IMMEDIATE},
    {0xE3, op::ISC, "ISC", 2, am::INDEXED_INDIRECT},
    {0xE4, op::CPX, "CPX", 2, am::ZERO_PAGE},
    {0xE5, op::SBC, "SBC", 2, am::ZERO_PAGE},
    {0xE6, op::INC, "INC", 2, am::ZERO_PAGE},
    {0xE7, op::ISC, "ISC", 2, am::ZERO_PAGE},
    {0xE8, op::INX, "INX", 1, am::IMPLICIT},
    {0xE9, op::SBC, "SBC", 2, am::IMMEDIATE},
    {0xEA, op::NOP, "NOP", 1, am::IMPLICIT},
    {0xEB, op::SBC, "SBC", 2, am::IMMEDIATE},
    {0xEC, op::CPX, "CPX", 3, am::ABSOLUTE},
    {0xED, op::SBC, "SBC", 3, am::ABSOLUTE},
    {0xEE, op::INC, "INC", 3, am::ABSOLUTE},
    {0xEF, op::ISC, "ISC", 3, am::ABSOLUTE},

    {0xF0, op::BEQ, "BEQ", 2, am::RELATIVE},
    {0xF1, op::SBC, "SBC", 2, am::INDIRECT_INDEXED},
    {0xF2, op::STP, "STP", 1, am::IMPLICIT},
    {0xF3, op::ISC, "ISC", 2, am::INDIRECT_INDEXED},
    {0xF4, op::NOP, "NOP", 2, am::ZERO_PAGE_X},
    {0xF5, op::SBC, "SBC", 2, am::ZERO_PAGE_X},
    {0xF6, op::INC, "INC", 2, am::ZERO_PAGE_X},
    {0xF7, op::ISC, "ISC", 2, am::ZERO_PAGE_X},
    {0xF8, op::SED, "SED", 1, am::IMPLICIT},
    {0xF9, op::SBC, "SBC", 3, am::ABSOLUTE_Y},
    {0xFA, op::NOP, "NOP", 1, am::IMPLICIT},
    {0xFB, op::ISC, "ISC", 3, am::ABSOLUTE_Y},
    {0xFC, op::NOP, "NOP", 3, am::ABSOLUTE_X},
    {0xFD, op::SBC, "SBC", 3, am::ABSOLUTE_X},
    {0xFE, op::INC, "INC", 3, am::ABSOLUTE_X},
    {0xFF, op::ISC, "ISC", 3, am::ABSOLUTE_X},
};

} // namespace jones
