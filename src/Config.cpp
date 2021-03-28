#include "header.h"

// *****************************************************************************

Config::Config()
{
  if (DEBUG_MODE == 1)
  {
    Serial.println("Config init");
  }
}

// *****************************************************************************

void Config::show(int counter)
{
  char msg[16];
  switch (_menuOption)
  {
  case MenuOptions::buzzer:
    sprintf(msg, "Buzzer %s", _options.buzzerOn ? "      ON" : "     OFF");
    break;
  case MenuOptions::lcdAlwaysOn:
    sprintf(msg, "LCD %s", _options.lcdAlwaysOn ? "         ON" : "     DEMAND");
    break;
  case MenuOptions::direction:
    sprintf(msg, "Spool in %s", _options.direction == 1 ? "   TOP" : "  DOWN");
    break;
  case MenuOptions::exit:
    sprintf(msg, "Exit           ");
    break;
  }
  counter == -1 ? display->printMsg(msg, 1) : display->printHold(msg, counter);
}

void Config::changeOption()
{
  switch (_menuOption)
  {
  case MenuOptions::buzzer:
    setBuzzerOn(!_options.buzzerOn);
    show();
    break;
  case MenuOptions::lcdAlwaysOn:
    setLcdAlwaysOn(!_options.lcdAlwaysOn);
    show();
    break;
  case MenuOptions::direction:
    setDirection(-_options.direction);
    show();
    break;
  case MenuOptions::exit:
    storage->writeOptions();
    menu->setMode(Menu::Mode::holdForConfig);
    _menuOption = MenuOptions::buzzer;
    display->clear(1);
    break;
  }
}

void Config::setBuzzerOn(bool isBuzzerOn)
{
  if (DEBUG_MODE == 1)
  {
    Serial.print("Buzzer set ");
    Serial.println(isBuzzerOn ? "on" : "off");
  }
  _options.buzzerOn = isBuzzerOn;
}
void Config::setLcdAlwaysOn(bool isLcdAlwaysOn)
{
  if (DEBUG_MODE == 1)
  {
    Serial.print("LCD set ");
    Serial.println(isLcdAlwaysOn ? "on" : "off");
  }
  _options.lcdAlwaysOn = isLcdAlwaysOn;
}
void Config::setDirection(double direction)
{
  if (DEBUG_MODE == 1)
  {
    Serial.print("Direction set ");
    Serial.println(direction);
  }
  _options.direction = direction == 1 ? 1 : -1;
}

bool Config::isBuzzerOn() { return _options.buzzerOn; }
bool Config::isLcdAlwaysOn() { return _options.lcdAlwaysOn; }
double Config::getDirection() { return _options.direction; }
void Config::nextOption()
{
  switch (_menuOption)
  {
  case MenuOptions::buzzer:
    _menuOption = MenuOptions::lcdAlwaysOn;
    break;
  case MenuOptions::lcdAlwaysOn:
    _menuOption = MenuOptions::direction;
    break;
  case MenuOptions::direction:
    _menuOption = MenuOptions::exit;
    break;
  case MenuOptions::exit:
    _menuOption = MenuOptions::buzzer;
    break;
  }
  show();
}