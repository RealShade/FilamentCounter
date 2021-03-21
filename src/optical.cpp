#include "display.h"
#include "header.h"

int pair1PrevState = LOW;
int pair2PrevState = LOW;

void setupPair() {
  pinMode(PAIR1PIN, INPUT);
  pinMode(PAIR2PIN, INPUT);
  pair1PrevState = digitalRead(PAIR1PIN);
  pair2PrevState = digitalRead(PAIR2PIN);
}

void loopPair() {
  int pair1State = digitalRead(PAIR1PIN);
  int pair2State = digitalRead(PAIR2PIN);
  if (pair1PrevState != pair1State) {
    if (pair1State == LOW && pair2PrevState != pair2State) {
      st->incSpent((pair2State == HIGH ? 1 : -1) * ROLLLENGTH);
      printSpent(st->getSpent());
    }
    pair1PrevState = pair1State;
    pair2PrevState = pair2State;
  }
}
