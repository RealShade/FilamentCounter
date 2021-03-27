#include "header.h"

Optocoupler::Optocoupler() {
  if (DEBUG_MODE == 1) {
    Serial.println("Optocoupler init");
  }
  pinMode(PAIR_1_PIN, INPUT);
  pinMode(PAIR_2_PIN, INPUT);
  _prevState1 = digitalRead(PAIR_1_PIN);
  _prevState2 = digitalRead(PAIR_2_PIN);
}

void Optocoupler::check() {
  int state1 = digitalRead(PAIR_1_PIN);
  int state2 = digitalRead(PAIR_2_PIN);

  if (_prevState1 != state1) {
    if (DEBUG_MODE == 1) {
      Serial.print("Octocoupler change status: ");
      Serial.println(state1);
    }
    if (state1 == LOW && _prevState2 != state2) {
      spool->incSpent((state2 == HIGH ? 1 : -1) * GEAR_CIRCUMFERENCE);
      display->printSpent();
    }
    _prevState1 = state1;
    _prevState2 = state2;
  }
}
