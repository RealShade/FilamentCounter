#include "header.h"

#define CYCLE_BUZZ_LENGTH 1000    // HIGH length
#define CYCLE_SILENT_LENGTH 2000 // LOW length
#define CLICK_LENGTH 50         // Click length

// *****************************************************************************

Buzzer::Buzzer()
{
    pinMode(BUZZER_PIN, OUTPUT);
}

// *****************************************************************************

void Buzzer::check()
{
    if (!config->isBuzzerOn())
        return;

    switch (_mode)
    {
    case Mode::alarm:
        if (_timeStart + (_state ? CYCLE_BUZZ_LENGTH : CYCLE_SILENT_LENGTH) <= millis())
        {
            _state = !_state;
            digitalWrite(BUZZER_PIN, _state ? HIGH : LOW);
            _timeStart = millis();
            if (DEBUG_MODE == 1)
            {
                Serial.print("Buzzer state change to ");
                Serial.println(_state ? "buzz" : "silent");
            }
        }
        break;
    case Mode::click:
        if (_timeStart + CLICK_LENGTH <= millis())
        {
            buzzerOff();
            if (DEBUG_MODE == 1)
            {
                Serial.println("Buzer click off");
            }
        }
        break;
    default:
        break;
    }
}

void Buzzer::alarmStart()
{
    if (_mode != Mode::off || !config->isBuzzerOn())
        return;

    if (DEBUG_MODE == 1)
    {
        Serial.println("Buzzer on (alarm)");
    }
    digitalWrite(BUZZER_PIN, HIGH);
    _mode = Mode::alarm;
    _state = true;
    _timeStart = millis();
}

void Buzzer::clickStart()
{
    if (_mode != Mode::off || !config->isBuzzerOn())
        return;

    if (DEBUG_MODE == 1)
    {
        Serial.println("Buzzer on (click)");
    }
    digitalWrite(BUZZER_PIN, HIGH);
    _mode = Mode::click;
    _timeStart = millis();
    _state = true;
}

void Buzzer::buzzerOff()
{
    if (!config->isBuzzerOn())
        return;

    if (DEBUG_MODE == 1)
    {
        Serial.println("Buzzer off");
    }
    digitalWrite(BUZZER_PIN, LOW);
    _mode = Mode::off;
}
