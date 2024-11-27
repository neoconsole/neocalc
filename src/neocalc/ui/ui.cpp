#include "../../../include/neocalc/ui/ui.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

neocalc::ui::ui() {
  std::string inputValue;

  auto inputBox = ftxui::Renderer([&] {
    return ftxui::hbox({
               ftxui::text(inputValue) | ftxui::focus | color(ftxui::Color::White),
           }) |
           ftxui::border;
  });

  auto inputHandler = CatchEvent(inputBox, [&](const ftxui::Event &event) {
    if (event.is_character()) {
      inputValue += event.character();
      return true;
    }
    if (event == ftxui::Event::Backspace && !inputValue.empty()) {
      inputValue.pop_back();
      return true;
    }
    return false;
  });

  auto screen = ftxui::ScreenInteractive::TerminalOutput();
  screen.Loop(inputHandler);
}
