#include "header.h"

char msg[16];
void Display::printUUID() {
  clear(0);
  printMsg(spool.getUUID(), 0);
}
void Display::printSpent() {
  dtostrf(spool.getSpent(), 7, 2, msg);
  clear(1);
  printMsg(msg, 1);
}
void Display::printHold(const char *text, int counter = 0) {
  clear(1);
  sprintf(msg, "%s%c", text, char(counter));
  printMsg(msg, 1);
}
void Display::clear(short row) {
  printMsg("                ", row);
}
void Display::printMsg(const char *msg, short row = 0) {
  lcd.setCursor(0, row);
  lcd.print(msg);
  Serial.println(msg);
}
