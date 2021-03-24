#include "header.h"

int seconds;

Button::Button() {
  pinMode(BUTTON_PIN, INPUT);
  _prevState = digitalRead(BUTTON_PIN);
  _pressTimeStart = millis();
}

void Button::check() {
  int __currentState = digitalRead(BUTTON_PIN);

  if (__currentState != _prevState) {
    _prevState = __currentState;
    _pressTimeStart = millis();
    _counter = HOLD_COUNTER + 1;

    // If button release
    if (__currentState == LOW) {
      switch (menu.getMode()) {
      case Menu::spent:
        menu.setMode(Menu::holdForConfig);
        break;
      case Menu::holdForConfig:
        menu.setMode(Menu::holdForReset);
        break;
      case Menu::holdForReset:
        menu.setMode(Menu::spent);
        break;
      }
      menu.show();
    }
  } else if (__currentState == HIGH) {
    if (millis() - _pressTimeStart > HOLD_DETECT) {
      seconds = static_cast<int>((millis() - _pressTimeStart)*2);
      if (seconds < HOLD_COUNTER) {
        if (_counter > HOLD_COUNTER - seconds) {
          _counter = HOLD_COUNTER - seconds;
          menu.show();
        }
      } else {
        switch (menu.getMode()) {
        case Menu::holdForConfig:
          menu.setMode(Menu::config);
          break;
        case Menu::holdForReset:
          menu.setMode(Menu::reset);
          break;
        }
        menu.show();
      }
    }
  }
}
