#include "header.h"

// *****************************************************************************

Config::Config()
{
  byte options;
  if (DEBUG_MODE == 1)
    Serial.println("Config init");
  options = storage->readOptions();
  if (options == 255)
  {
    if (DEBUG_MODE)
      Serial.println("init default options");
    storage->writeOptions(_packOptions());
  }
  else
    _unpackOptions(options);
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
  case MenuOptions::endstop:
    sprintf(msg, "Endstop %s", _options.endstop ? "      ON" : "     OFF");
    break;
  case MenuOptions::exit:
    sprintf(msg, "Exit           ");
    break;
  }
  counter == -1 ? display->printMsg(msg, 1) : display->printHold(msg, counter);
}

void Config::holdedOption()
{
  switch (_menuOption)
  {
  case MenuOptions::buzzer:
    _setBuzzerOn(!_options.buzzerOn);
    show();
    break;
  case MenuOptions::lcdAlwaysOn:
    _setLcdAlwaysOn(!_options.lcdAlwaysOn);
    show();
    break;
  case MenuOptions::direction:
    _setDirection(-_options.direction);
    show();
    break;
  case MenuOptions::endstop:
    _setEndstopOn(!_options.endstop);
    show();
    break;
  case MenuOptions::exit:
    storage->writeOptions(_packOptions());
    menu->setMode(Menu::Mode::holdForConfig);
    _menuOption = MenuOptions::buzzer;
    display->clear(1);
    break;
  }
}

bool Config::isBuzzerOn() { return _options.buzzerOn; }
bool Config::isLcdAlwaysOn() { return _options.lcdAlwaysOn; }
double Config::getDirection() { return _options.direction; }
bool Config::isEndstopOn() { return _options.endstop; }

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
    _menuOption = MenuOptions::endstop;
    break;
  case MenuOptions::endstop:
    _menuOption = MenuOptions::exit;
    break;
  case MenuOptions::exit:
    _menuOption = MenuOptions::buzzer;
    break;
  }
  show();
}

// *****************************************************************************

void Config::_setBuzzerOn(bool isBuzzerOn)
{
  if (DEBUG_MODE == 1)
  {
    Serial.print("Buzzer set ");
    Serial.println(isBuzzerOn ? "on" : "off");
  }
  _options.buzzerOn = isBuzzerOn;
}
void Config::_setLcdAlwaysOn(bool isLcdAlwaysOn)
{
  if (DEBUG_MODE == 1)
  {
    Serial.print("LCD set ");
    Serial.println(isLcdAlwaysOn ? "on" : "off");
  }
  _options.lcdAlwaysOn = isLcdAlwaysOn;
}
void Config::_setDirection(double direction)
{
  if (DEBUG_MODE == 1)
  {
    Serial.print("Direction set ");
    Serial.println(direction);
  }
  _options.direction = direction == 1 ? 1 : -1;
}
void Config::_setEndstopOn(bool isEndstopOn)
{
  if (DEBUG_MODE == 1)
  {
    Serial.print("Endstop set ");
    Serial.println(isEndstopOn ? "on" : "off");
  }
  _options.endstop = isEndstopOn;
}

void Config::_unpackOptions(byte options)
{
  _setBuzzerOn(options & BIT_BUZZER);
  _setLcdAlwaysOn(options & BIT_LCD_ALWAYS_ON);
  _setDirection(options & BIT_DIRECTION ? 1 : -1);
  _setEndstopOn(options & BIT_ENDSTOP);
}

byte Config::_packOptions()
{
  return static_cast<byte>(isBuzzerOn()) * BIT_BUZZER +
         static_cast<byte>(isLcdAlwaysOn()) * BIT_LCD_ALWAYS_ON +
         static_cast<byte>(getDirection() == 1) * BIT_DIRECTION +
         static_cast<byte>(isEndstopOn()) * BIT_ENDSTOP;
}
