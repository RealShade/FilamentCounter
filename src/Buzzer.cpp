#include "header.h"

#define CYCLE_BUZZ_LENGTH = 500    // HIGH length
#define CYCLE_SILENT_LENGTH = 1000 // LOW length

Buzzer::Buzzer()
{
    pinMode(BUZZER_PIN, OUTPUT);
}

void Buzzer::check()
{
    if (!config->isBuzzerOn())
        return;
}

void Buzzer::alertStart()
{
    if (_state || !config->isBuzzerOn())
        return;
    if (DEBUG_MODE == 1)
    {
        Serial.println("Buzzer on");
    }
    digitalWrite(BUZZER_PIN, HIGH);
    _state = true;
}

void Buzzer::alertStop()
{
    if (!_state || !config->isBuzzerOn())
        return;
    if (DEBUG_MODE == 1)
    {
        Serial.println("Buzzer off");
    }
    digitalWrite(BUZZER_PIN, LOW);
    _state = false;
}
