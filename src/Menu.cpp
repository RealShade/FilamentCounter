#include "header.h"

// *****************************************************************************

Menu::Menu() {
  if (DEBUG_MODE == 1) {
    Serial.println("Menu init");
  }
}

// *****************************************************************************

Menu::Mode Menu::getMode() { return _mode; }

// *****************************************************************************

void Menu::setMode(Mode mode) {
  _mode = mode;
  show();
  if (DEBUG_MODE == 1) {
    Serial.print("Set mode: ");
    Serial.println((int)mode);
  }
}

void Menu::show(int counter) {
  switch (_mode) {
  case Mode::waitForFilament:
    display->printMsg("Wait for spool", 0);
    break;
  case Mode::spent:
    display->printUUID();
    display->printSpent();
    break;
  case Mode::holdForConfig:
    display->printHold("Hold for conf", counter);
    break;
  case Mode::holdForReset:
    display->printHold("Hold for reset", counter);
    break;
  case Mode::config:
    config->show();
    break;
  case Mode::reset:
    spool->setSpent(0);
    display->printMsg("Reset done", 1);
    break;
  }
}
