#include "header.h"

int pair1PrevState = LOW;
int pair2PrevState = LOW;

void setupPair() {
  pinMode(PAIR_1_PIN, INPUT);
  pinMode(PAIR_2_PIN, INPUT);
  pair1PrevState = digitalRead(PAIR_1_PIN);
  pair2PrevState = digitalRead(PAIR_2_PIN);
}

void loopPair() {
  int pair1State = digitalRead(PAIR_1_PIN);
  int pair2State = digitalRead(PAIR_2_PIN);
  if (pair1PrevState != pair1State) {
    if (pair1State == LOW && pair2PrevState != pair2State) {
      spool.incSpent((pair2State == HIGH ? 1 : -1) * GEAR_CIRCUMFERENCE);
      display.printSpent();
    }
    pair1PrevState = pair1State;
    pair2PrevState = pair2State;
  }
}
