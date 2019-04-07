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
#define BOOST_TEST_MODULE test_suite_nes_test

#include <boost/core/ignore_unused.hpp>
#include <boost/test/unit_test.hpp>
#include <nes.hh>
#include <nes_rom.hh>

#include "nes.hh"
#include "nes_rom.hh"

namespace {

void trace_rom(const char *rom_path, const char *trace_path) {
  boost::ignore_unused(rom_path);
  boost::ignore_unused(trace_path);

  jones::nes_rom rom(rom_path);
  //  jones::nes nes;
  //  nes.load(rom);
}

} // namespace

BOOST_AUTO_TEST_CASE(test_suite_nes_test) {
  BOOST_CHECK(true);
  trace_rom("", "");
}