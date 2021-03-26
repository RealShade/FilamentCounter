#include "header.h"

void Menu::setMode(Mode mode) { _mode = mode; }

Menu::Mode Menu::getMode() { return _mode; }

void Menu::show(int counter) {
  switch (_mode) {
  case Mode::waitForFilament:
    display.printMsg("Wait for spool", 0);
    break;
  case Mode::spent:
    display.printUUID();
    display.printSpent();
    break;
  case Mode::holdForConfig:
    display.printHold("Hold for conf", counter);
    break;
  case Mode::holdForReset:
    display.printHold("Hold for reset", counter);
    break;
  case Mode::config:
    config.show();
    break;
  case Mode::reset:
    display.printMsg("Reset done", 1);
    break;
  }
}
