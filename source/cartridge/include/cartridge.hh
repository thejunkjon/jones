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
#ifndef JONES_CARTRIDGE_CARTRIDGE_HH
#define JONES_CARTRIDGE_CARTRIDGE_HH

#include <fstream>
#include <stdint.h>
#include <string>

#define ROM_HEADER_CONSTANT 0x1A53454E

namespace jones {

class Cartridge {

public:
  Cartridge(const std::string &pathToRom);

  bool isValid();

  int getHeaderVersion() const;

  void printHeader(std::ostream &out) const;

  uint16_t getPrgRomOffset() const;

  uint16_t getChrRomOffset() const;

private:
  struct RomHeader {
    uint32_t constants;
    uint8_t sizeOfPrgRom;
    uint8_t sizeOfChrRom;
    uint8_t hasMirroring : 1;
    uint8_t containsBatteryBackedPrgRam : 1;
    uint8_t hasTrainer : 1;
    uint8_t ignoreMirroringControl : 1;
    uint8_t lowerMapperNibble : 4;
    uint8_t isVsUnisystem : 1;
    uint8_t isPlayChoice : 1;
    uint8_t version : 2;
    uint8_t upperMapperNibble : 4;
    uint8_t sizeOfPrgRam;
    uint8_t whichTvSystemOne : 1;
    unsigned int : 7;
    uint8_t whichTvSystemTwo : 2;
    unsigned int : 2;
    uint8_t isPrgRamPresent : 1;
    uint8_t hasBusConflicts : 1;
    unsigned int : 2;
    uint8_t ignored[5];
  };

  RomHeader romFileHeader_;

  std::ifstream romFile_;
};
} // namespace jones

#endif // JONES_CARTRIDGE_CARTRIDGE_HH
