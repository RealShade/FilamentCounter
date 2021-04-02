#include "header.h"

#define CYCLE_BUZZ_LENGTH = 500    // HIGH length
#define CYCLE_SILENT_LENGTH = 1000 // LOW length

void Buzzer::check()
{
    if (!config->isBuzzerOn())
        return;
}

void Buzzer::alertStart()
{
    if (_state || !config->isBuzzerOn())
        return;
}

void Buzzer::alertStop()
{
    if (!_state || !config->isBuzzerOn())
        return;
}
