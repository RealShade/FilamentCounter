#include "display.h"
#include "header.h"

int buttonPrevState = LOW;
unsigned long buttonPressTimeStart;
int clearState = false;

void setupButton() {
  pinMode(BUTTONPIN, INPUT);
  buttonPrevState = digitalRead(BUTTONPIN);
  buttonPressTimeStart = millis();
}

void loopButton() {
  int buttonState = digitalRead(BUTTONPIN);
  if (buttonState != buttonPrevState) {
    buttonPressTimeStart = millis();
    clearState = false;
    if (buttonState == HIGH) {
      printMsg("Clear after 5   ");
    } else {
      printMsg("                ");
      printSpent(st->getSpent());
    }
    buttonPrevState = buttonState;
  } else if (buttonState == HIGH) {
    int idle = (millis() - buttonPressTimeStart) / 1000;
    if (idle < 5) {
      char str[16];
      sprintf(str, "Clear after %d   ", 5 - idle);
      printMsg(str);
    } else if (clearState == false) {
      printMsg("Clear done      ");
      clearState = true;
    }
  }
}
