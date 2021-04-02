#include "header.h"

void Endstop::check()
{
    int state = digitalRead(ENDSTOP_PIN);
    if (state == HIGH && _armed)
    {
        // Start alert
        buzzer->alertStart();
    }
    else if (state == LOW)
    {
        // Load filament
        if (!_armed)
            _armed = config->isEndstopOn();
        else
            buzzer->alertStop();
    }
}
