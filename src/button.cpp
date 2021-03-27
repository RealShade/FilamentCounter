#include "header.h"

int seconds;

Button::Button() {
  if (DEBUG_MODE) {
    Serial.println("Button init");
  }
  pinMode(BUTTON_PIN, INPUT);
  _prevState = digitalRead(BUTTON_PIN);
  _pressTimeStart = millis();
}

void Button::check() {
  _currentState = digitalRead(BUTTON_PIN);

  if (_currentState != _prevState) {
    if (DEBUG_MODE) {
      Serial.print("Button state: ");
      Serial.println(_currentState ? "push" : "release");
    }
    _pressTimeStart = millis();
    _counter = HOLD_COUNTER + 1;

    // If button release
    if (_currentState == LOW) {
      switch (menu->getMode()) {
      case Menu::Mode::spent:
        menu->setMode(Menu::Mode::holdForConfig);
        break;
      case Menu::Mode::holdForConfig:
        menu->setMode(Menu::Mode::holdForReset);
        break;
      default:
        menu->setMode(Menu::Mode::spent);
        break;
      }
    }
    _prevState = _currentState;

  } else if (_currentState == HIGH) {

    if (millis() - _pressTimeStart > HOLD_DETECT) {
      seconds = static_cast<int>((millis() - _pressTimeStart) * 2);
      if (seconds < HOLD_COUNTER) {
        if (_counter > HOLD_COUNTER - seconds) {
          _counter = HOLD_COUNTER - seconds;
          menu->show(_counter);
        }
      } else {
        switch (menu->getMode()) {
        case Menu::Mode::holdForConfig:
          menu->setMode(Menu::Mode::config);
          break;
        case Menu::Mode::holdForReset:
          menu->setMode(Menu::Mode::reset);
          spool->reset();
          break;
        default:
          menu->setMode(Menu::Mode::spent);
        }
      }
    }
  }
}
