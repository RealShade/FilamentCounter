#include "header.h"

// *****************************************************************************

Config::Config() {
  if (DEBUG_MODE == 1) {
    Serial.println("Config init");
  }
}

// *****************************************************************************

void Config::show() {
  switch (_menuOption) {
  case MenuOptions::notImplemented:
    display->printMsg("Not implemented", 1);
    break;
  }
}

// *****************************************************************************

void Config::setBuzzerOn(bool isBuzzerOn) {
  if (DEBUG_MODE == 1) {
    Serial.print("Buzzer set ");
    Serial.println(isBuzzerOn ? "on" : "off");
  }
  _options.buzzerOn = isBuzzerOn;
}
void Config::setLcdAlwaysOn(bool isLcdAlwaysOn) {
  if (DEBUG_MODE == 1) {
    Serial.print("LCD set ");
    Serial.println(isLcdAlwaysOn ? "on" : "off");
  }
  _options.lcdAlwaysOn = isLcdAlwaysOn;
}
void Config::setDirection(double direction) {
  if (DEBUG_MODE == 1) {
    Serial.print("Direction set ");
    Serial.println(direction);
  }
  _options.direction = direction == 1 ? 1 : -1;
}

// *****************************************************************************

bool Config::isBuzzerOn() { return _options.buzzerOn; }
bool Config::isLcdAlwaysOn() { return _options.lcdAlwaysOn; }
double Config::getDirection() { return _options.direction; }
