#include "header.h"

// *****************************************************************************

Endstop::Endstop()
{
    pinMode(ENDSTOP_PIN, INPUT);
    _prevState = digitalRead(ENDSTOP_PIN);
}

// *****************************************************************************

void Endstop::check()
{
    int state = digitalRead(ENDSTOP_PIN);
    if (state != _prevState)
    {
        if (state == HIGH && _armed)
        {
            // Start alarm
            if (DEBUG_MODE == 1)
            {
                Serial.println("Filament end");
            }
            _alarm = true;
            buzzer->alarmStart();
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
            _alarm = false;
            buzzer->buzzerOff();
            _armed = config->isEndstopOn();
            if (menu->getMode() == Menu::Mode::spent)
            {
                display->printSpent();
            }
        }
    _prevState = state;
    }
}

bool Endstop::isAlarm()
{
    return _alarm;
}

void Endstop::resetAlarm()
{
    if (DEBUG_MODE == 1)
    {
        Serial.println("Alarm reset");
    }
    _armed = false;
    _alarm = false;
    buzzer->buzzerOff();
}