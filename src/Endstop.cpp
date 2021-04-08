#include "header.h"

Endstop::Endstop()
{
    pinMode(ENDSTOP_PIN, INPUT);
}

void Endstop::check()
{
    int state = digitalRead(ENDSTOP_PIN);
    if (state != _prevState)
    {
        if (state == HIGH && _armed)
        {
            // Start alert
            if (DEBUG_MODE == 1)
            {
                Serial.println("Filament end");
            }
            _alert = true;
            buzzer->alertStart();
            if (menu->getMode() == Menu::Mode::spent)
            {
                display->printSpent();
            }
        }
        else if (state == LOW)
        {
            // Load filament
            if (DEBUG_MODE == 1)
            {
                Serial.println("Filament load");
            }
            _alert = false;
            buzzer->alertStop();
            _armed = config->isEndstopOn();
            if (menu->getMode() == Menu::Mode::spent)
            {
                display->printSpent();
            }
        }
    }
    _prevState = state;
}

bool Endstop::isAlert()
{
    return _alert;
}

void Endstop::resetAlert()
{
    if (DEBUG_MODE == 1)
    {
        Serial.println("Alert reset");
    }
    _armed = false;
    _alert = false;
    buzzer->alertStop();
}