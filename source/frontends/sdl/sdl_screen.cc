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
#include <SDL2/SDL.h>
#include <boost/core/ignore_unused.hpp>
#include <cstdint>

#include "log.hh"
#include "sdl_screen.hh"

using namespace jones;

namespace {

void sdl_push_quit_event() {
  SDL_Event event;
  event.type = SDL_QUIT;
  SDL_PushEvent(&event);
}

void sdl_shutdown() {
  SDL_PumpEvents();
  SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
  SDL_Quit();
}

} // namespace

sdl_screen::sdl_screen(std::unique_ptr<sdl_screen_listener> listener) : listener_(std::move(listener)) {
}

sdl_screen::~sdl_screen() {
  uninitialize();
}

void sdl_screen::draw_pixel(const uint16_t x_position, const uint16_t y_position, const uint32_t pixel) {
  if (renderer_ != nullptr) {
    const auto red = pixel & 0xF000U;
    const auto green = pixel & 0xF00U;
    const auto blue = pixel & 0xF0U;
    const auto alpha = pixel & 0xFU;
    SDL_SetRenderDrawColor(renderer_, red, green, blue, alpha);
    SDL_RenderDrawPoint(renderer_, x_position, y_position);
  }
}

void sdl_screen::set_scale(const uint8_t scale) {
  scale_ = scale;
}

void sdl_screen::initialize() {
  show();
}

void sdl_screen::uninitialize() {
  hide();
}

void sdl_screen::show() {
  if (is_running_) {
    LOG_DEBUG << "screen is already being shown";
    return;
  }
  SDL_Init(SDL_INIT_HAPTIC);
  window_ = SDL_CreateWindow("Jones NES Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
  if (window_ == nullptr) {
    LOG_ERROR << "unable to create window";
    return;
  }
  renderer_ = SDL_CreateRenderer(window_, -1, 0);
  if (renderer_ == nullptr) {
    LOG_ERROR << "unable to create renderer";
    return;
  }
  fill_with_color(0, 0, 0, 0);
  running_thread_ = std::make_unique<std::thread>([this]() {
    is_running_ = true;
    while (is_running_) {
      process_events();
    }
  });
}

void sdl_screen::hide() {
  is_running_ = false;
  sdl_push_quit_event();
  if (running_thread_ != nullptr) {
    running_thread_->join();
    running_thread_ = nullptr;
  }
  if (renderer_ != nullptr) {
    SDL_DestroyRenderer(renderer_);
    renderer_ = nullptr;
  }
  if (window_ != nullptr) {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
  }
  sdl_shutdown();
}

void sdl_screen::fill_with_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
  if (renderer_ != nullptr) {
    SDL_SetRenderDrawColor(renderer_, r, g, b, a);
    SDL_RenderClear(renderer_);
    SDL_RenderPresent(renderer_);
  }
}

void sdl_screen::process_events() {
  SDL_Event events;
  while (SDL_PollEvent(&events)) {
    if (events.type == SDL_QUIT) {
      is_running_ = false;
      if (listener_ != nullptr) {
        listener_->on_screen_closed();
      }
      break;
    }
  }
}