#include "header.h"

Menu::Menu() {}
void Menu::setMode(Mode mode) { _mode = mode; }
Menu::Mode Menu::getMode() {
  return _mode;
}
void Menu::show(int counter) {
  switch (_mode) {
  case Menu::waitForFilament:
    display.printMsg("Wait for spool", 0);
    break;
  case Menu::spent:
    display.printSpent();
    break;
  case Menu::holdForConfig:
    display.printHold("Hold for conf", counter);
    break;
  case Menu::config:
    break;
  case Menu::holdForReset:
    display.printHold("Hold for reset", counter);
    break;
  case Menu::reset:
    break;
  }
}
