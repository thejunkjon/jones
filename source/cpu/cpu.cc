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
#include "cpu.h"

using namespace jones;

//
// CPU reference
// http://e-tradition.net/bytes/6502/6502_instruction_set.html
//
namespace {

  enum class InstructionSet {

    // add with carry
    ADC,

    // and (with accumulator)
    AND,

    // arithmetic shift left
    ASL,

    // branch on carry clear
    BCC,

    // branch on carry set
    BCS,

    // branch on equal (zero set)
    BEQ,

    // bit test
    BIT,

    // branch on minus (negative set)
    BMI,

    // branch on not equal (zero clear)
    BNE,

    // branch on plus (negative clear)
    BPL,

    // interrupt
    BRK,

    // branch on overflow clear
    BVC,

    // branch on overflow set
    BVS,

    // clear carry
    CLC,

    // clear decimal
    CLD,

    // clear interrupt disable
    CLI,

    // clear overflow
    CLV,

    // compare (with accumulator)
    CMP, 

    // compare with X
    CPX,

    // compare with Y
    CPY,

    // decrement
    DEC,

    // decrement X
    DEX, 

    // decrement Y
    DEY, 

    // exclusive or (with accumulator)
    EOR,

    // increment
    INC,

    // increment x
    INX,

    // increment y
    INY,

    // jump
    JMP,

    // jump subroutine
    JSR,

    // load accumulator
    LDA,

    // load x
    LDX,

    // load y
    LDY,

    // logical shift right
    LSR,

    // no operation
    NOP,

    // or with accumulator
    ORA,

    // push accumulator
    PHA,

    // push processor status (SR)
    PHP,

    // pull accumulator
    PLA,

    // pull processor status (SR)
    PLP,

    // rotate left
    ROL,

    // rotate right
    ROR,

    // return from interrupt
    RTI,

    // return from subroutine
    RTS,

    // subtract with carry
    SBC,

    // set carry
    SEC,

    // set decimal
    SED,

    // set interrupt disable
    SEI,

    // store accumulator
    STA,

    // store X
    STX,

    // store y
    STY,

    // transfer accumulator to X
    TAX,

    // transfer accumulator to Y
    TAY,

    // transfer stack pointer to X
    TSX,

    // transfer stack pointer to Y
    TSY,

    // transfer X to accumulator
    TXA,

    // transfer X to stack pointer
    TXS,

    // transfer Y to accumulator
    TYA,

    // transfer Y to stack pointer
    TYS
  };
  
  enum class Registers {

    // program counter (16 bit)
    PC,
    
    // accumulator (8 bit)
    AC,

    // X register (8 bit)
    X,

    // Y register (8 bit)
    Y,

    // status register (8 bit)
    SR,
    
    // stack pointer (8 bit)
    SP
  };

  enum class StatusRegisterFlags {
    // Negative
    N,

    // Overflow
    V,

    // Break
    B,

    // Decimal (use BCD for arithmetics)
    D,

    // Interrupt (IRQ disable)
    I,

    // Zero
    Z,

    // Carry
    C,
  };
}

Cpu::Cpu(const void* baseAddress) {
}

void Cpu::reset() {
}

void Cpu::run() {
}

void* Cpu::getProgramCounter() {
}

void Cpu::setProgramCounter(const unsigned int address) {
}
