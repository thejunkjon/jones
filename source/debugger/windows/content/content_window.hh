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
#ifndef JONES_DEBUGGER_WINDOWS_CONTENT_WINDOW_HH
#define JONES_DEBUGGER_WINDOWS_CONTENT_WINDOW_HH

#include <curses.h>

#include "window.hh"

namespace jones::windows {

class content_window final : public windows::window {

public:
  explicit content_window(WINDOW *parent_window);

  ~content_window() override;

  windows::window_type type() override;

  void on_focus() override;

  void on_unfocus() override;

  void on_key_pressed(int key) override;

  void draw(int start_y, int start_x, int line_count, int column_count) override;

private:
  WINDOW *parent_window_;

  WINDOW *window_;
};

} // namespace jones::windows

#endif // JONES_DEBUGGER_WINDOWS_CONTENT_WINDOW_HH