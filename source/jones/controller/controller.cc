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
#include "controller.hh"

#include <boost/core/ignore_unused.hpp>
#include <boost/static_assert.hpp>
#include <map>

using namespace jones;

using button = jones::controller::button;
using button_state = jones::controller::button_state;
using button_state_map = std::map<button, button_state>;

namespace {

button position_to_button(const uint8_t position) {
  switch (position) {
  case 0:
    return button::BUTTON_A;
  case 1:
    return button::BUTTON_B;
  case 2:
    return button::BUTTON_SELECT;
  case 3:
    return button::BUTTON_START;
  case 4:
    return button::BUTTON_UP;
  case 5:
    return button::BUTTON_DOWN;
  case 6:
    return button::BUTTON_LEFT;
  case 7:
    return button::BUTTON_RIGHT;
  default:
    BOOST_STATIC_ASSERT("unexpected button found");
    return button::BUTTON_INVALID;
  }
}

} // namespace

const char *controller::button_to_string(const button button) {
  switch (button) {
  case button::BUTTON_A:
    return "BUTTON_A";
  case button::BUTTON_B:
    return "BUTTON_B";
  case button::BUTTON_SELECT:
    return "BUTTON_SELECT";
  case button::BUTTON_START:
    return "BUTTON_START";
  case button::BUTTON_UP:
    return "BUTTON_UP";
  case button::BUTTON_DOWN:
    return "BUTTON_DOWN";
  case button::BUTTON_LEFT:
    return "BUTTON_LEFT";
  case button::BUTTON_RIGHT:
    return "BUTTON_RIGHT";
  default:
    return "BUTTON_INVALID";
  }
}

const char *controller::button_state_to_string(const button_state button_state) {
  switch (button_state) {
  case button_state::BUTTON_STATE_DOWN:
    return "BUTTON_STATE_DOWN";
  case button_state::BUTTON_STATE_UP:
    return "BUTTON_STATE_UP";
  default:
    return "BUTTON_STATE_INVALID";
  }
}

class controller::controller::impl {
public:
  explicit impl(const memory &memory)
      : memory_(memory), strobe_(0), index_(0), button_states_(), controller_state_(controller_state::DISCONNECTED) {
    boost::ignore_unused(memory_);
  }

  ~impl() = default;

  auto set_button_state(const button button, const button_state state) -> void {
    button_states_[button] = state;
  }

  auto set_controller_state(const controller_state state) -> void {
    controller_state_ = state;
  }

  auto read(const uint16_t address) -> uint8_t {
    boost::ignore_unused(address);
    uint8_t data = 0;
    if (index_ < 8 && button_states_[position_to_button(index_)] == button_state::BUTTON_STATE_DOWN) {
      data = 1;
    }
    index_++;
    update_button_index();
    return data;
  }

  auto write(const uint16_t address, const uint8_t data) -> void {
    boost::ignore_unused(address);
    strobe_ = data;
    update_button_index();
  }

private:
  auto update_button_index() -> void {
    if ((strobe_ & 0x1U) == 1) {
      index_ = 0;
    }
  }

private:
  const memory &memory_;

  uint8_t strobe_;

  uint8_t index_;

  button_state_map button_states_;

  controller_state controller_state_;
};

controller::controller::controller(const memory &memory)
    : impl_(std::make_unique<impl>(memory)) {
}

controller::controller::~controller() = default;

auto controller::controller::set_button_state(const button button, const button_state state) -> void {
  impl_->set_button_state(button, state);
}

auto controller::controller::set_controller_state(const controller_state state) -> void {
  impl_->set_controller_state(state);
}

auto controller::controller::read(const uint16_t address) -> uint8_t {
  return impl_->read(address);
}

auto controller::controller::write(const uint16_t address, const uint8_t data) -> void {
  impl_->write(address, data);
}
