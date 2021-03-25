#include "header.h"

OpticalPair::OpticalPair() {
  pinMode(PAIR_1_PIN, INPUT);
  pinMode(PAIR_2_PIN, INPUT);
  _prevState1 = digitalRead(PAIR_1_PIN);
  _prevState2 = digitalRead(PAIR_2_PIN);
}

void OpticalPair::check() {
  _state1 = digitalRead(PAIR_1_PIN);
  _state2 = digitalRead(PAIR_2_PIN);

  if (_prevState1 != _state1) {
    if (_state1 == LOW && _prevState2 != _state2) {
      spool->incSpent((_state2 == HIGH ? 1 : -1) * GEAR_CIRCUMFERENCE);
      display.printSpent();
    }
    _prevState1 = _state1;
    _prevState2 = _state2;
  }
}
