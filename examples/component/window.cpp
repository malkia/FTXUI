// Copyright 2023 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;

Component DummyWindowContent() {
  class Impl : public ComponentBase {
   private:
    bool checked[3] = {false, false, false};
    float slider = 50;

   public:
    Impl() {
      Add(Container::Vertical({
          Checkbox("Check me", &checked[0]),
          Checkbox("Check me", &checked[1]),
          Checkbox("Check me", &checked[2]),
          Slider("Slider", &slider, 0.f, 100.f),
      }));
    }
  };
  return Make<Impl>();
}

int main() {
  int window_1_left = 20;
  int window_1_top = 10;
  int window_1_width = 40;
  int window_1_height = 20;

  WindowOptions options_1;
  options_1.inner = DummyWindowContent();
  options_1.title = "First window";
  options_1.left = &window_1_left;
  options_1.top = &window_1_top;
  options_1.width = &window_1_width;
  options_1.height = &window_1_height;
  auto window_1 = Window(options_1);

  WindowOptions options_2;
  options_2.inner = DummyWindowContent();
  options_2.title = "My window";
  options_2.left = 40;
  options_2.top = 20;
  auto window_2 = Window(options_2);

  WindowOptions options_3;
  options_3.inner = DummyWindowContent();
  options_3.title = "My window";
  options_3.left = 60;
  options_3.top = 30;
  auto window_3 = Window(options_3);

  WindowOptions options_4;
  options_4.inner = DummyWindowContent();
  auto window_4 = Window(options_4);

  auto window_5 = Window({});

  auto window_container = Container::Stacked({
      window_1,
      window_2,
      window_3,
      window_4,
      window_5,
  });

  auto display_win_1 = Renderer([&] {
    return text("window_1: " +  //
                std::to_string(window_1_width) + "x" +
                std::to_string(window_1_height) + " + " +
                std::to_string(window_1_left) + "," +
                std::to_string(window_1_top));
  });

  auto layout = Container::Vertical({
      display_win_1,
      window_container,
  });

  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(layout);

  return EXIT_SUCCESS;
}
