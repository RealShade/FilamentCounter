#include "header.h"

// *****************************************************************************

Menu::Menu()
{
  if (DEBUG_MODE == 1)
  {
    Serial.println("Menu init");
  }
}

// *****************************************************************************

Menu::Mode Menu::getMode() { return _mode; }

// *****************************************************************************

void Menu::setMode(Mode mode)
{
  _mode = mode;
  show();
  if (DEBUG_MODE == 1)
  {
    Serial.print("Set mode: ");
    Serial.println(static_cast<int>(mode));
  }
}

void Menu::show(int counter)
{
  switch (_mode)
  {
  case Mode::waitForFilament:
    display->clear(1);
    display->printMsg("Wait for spool  ", 0);
    break;
  case Mode::spent:
    display->printUuid();
    display->printSpent();
    break;
  case Mode::holdForUnloadSpool:
    display->printHold("Hld4unloadSpool", counter);
    break;
  case Mode::holdForConfig:
    display->printHold("Hld4setOptions", counter);
    break;
  case Mode::holdForReset:
    display->printHold("Hld4resetSpool", counter);
    break;
  case Mode::holdForClear:
    display->printHold("Hld4clearEEPROM", counter);
    break;
  case Mode::unload:
    if (spool != NULL)
    {
      spool->write();
      free(spool);
    }
    display->printMsg("Spool unloaded  ", 1);
    break;
  case Mode::config:
    config->show();
    break;
  case Mode::reset:
    spool->reset();
    display->printMsg("Spool reseted   ", 1);
    break;
  case Mode::clearEEPROM:
    storage->clearEEPROM();
    display->printMsg("EEPROM cleared  ", 1);
    break;
  }
}
