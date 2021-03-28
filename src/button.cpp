#include "header.h"

Button::Button()
{
  if (DEBUG_MODE)
  {
    Serial.println("Button init");
  }
  pinMode(BUTTON_PIN, INPUT);
  _prevState = digitalRead(BUTTON_PIN);
  _pressTimeStart = millis();
}

void Button::check()
{
  _currentState = digitalRead(BUTTON_PIN);

  if (_currentState != _prevState)
  {
    if (DEBUG_MODE)
    {
      Serial.print("Button state: ");
      Serial.println(_currentState ? "push" : "release");
    }

    // If button release
    if (_currentState == LOW)
    {
      switch (menu->getMode())
      {
      case Menu::Mode::spent:
      case Menu::Mode::waitForFilament:
        menu->setMode(Menu::Mode::holdForConfig);
        break;
      case Menu::Mode::holdForConfig:
        spool == NULL ? menu->setMode(Menu::Mode::holdForClear) : menu->setMode(Menu::Mode::holdForReset);
        break;
      case Menu::Mode::holdForReset:
        menu->setMode(Menu::Mode::holdForClear);
        break;
      case Menu::Mode::config:
        if (_counter > -1)
        {
          config->nextOption();
        }
        break;
      default:
        spool == NULL ? menu->setMode(Menu::Mode::waitForFilament) : menu->setMode(Menu::Mode::spent);
        break;
      }
    }

    _pressTimeStart = millis();
    _counter = HOLD_COUNTER + 1;
    _prevState = _currentState;
  }
  else if (_currentState == HIGH)
  {
    // If button hold
    if (_counter > -1 && (menu->getMode() == Menu::Mode::holdForConfig || menu->getMode() == Menu::Mode::holdForReset || menu->getMode() == Menu::Mode::holdForClear || menu->getMode() == Menu::Mode::config))
    {
      if (millis() - _pressTimeStart > HOLD_DETECT)
      {
        int seconds = static_cast<int>((millis() - _pressTimeStart) * 2 / 1000);
        if (seconds < HOLD_COUNTER)
        {
          if (_counter > HOLD_COUNTER - seconds)
          {
            _counter = HOLD_COUNTER - seconds;
            menu->getMode() == Menu::Mode::config ? config->show(_counter) : menu->show(_counter);
          }
        }
        else
        {
          switch (menu->getMode())
          {
          case Menu::Mode::holdForConfig:
            menu->setMode(Menu::Mode::config);
            break;
          case Menu::Mode::holdForReset:
            menu->setMode(Menu::Mode::reset);
            break;
          case Menu::Mode::holdForClear:
            menu->setMode(Menu::Mode::clearEEPROM);
            break;
          case Menu::Mode::config:
            config->changeOption();
            break;
          default:
            menu->setMode(Menu::Mode::spent);
            break;
          }
          // Prevent further processing hold button more
          _counter = -1;
        }
      }
    }
  }
}
