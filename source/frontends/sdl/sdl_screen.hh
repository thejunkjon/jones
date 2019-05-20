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
#ifndef JONES_SDL_SDL_SCREEN_HH
#define JONES_SDL_SDL_SCREEN_HH

#include "screen.hh"

#include <SDL2/SDL.h>

namespace jones {

class sdl_screen : public screen::screen {
public:
  ~sdl_screen() override = default;

  void initialize();

  void release();

  void draw_pixel(uint16_t x_position, uint16_t y_position) override;

  void set_scale(uint8_t scale) override;

private:
  void fill_with_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  void process_events();

  void show();

  void render_screen();

private:
  SDL_Event events_;

  SDL_Window *window_;

  SDL_Renderer *renderer_;

  bool is_running_;
};

} // namespace jones

#endif // JONES_SDL_SDL_SCREEN_HH
