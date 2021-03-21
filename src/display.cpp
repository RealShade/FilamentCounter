#include "header.h"

char msg[7];
void printSpent(double spent) {
  lcd.setCursor(0, 1);
  dtostrf(spent, 7, 2, msg);
  lcd.print(msg);
  Serial.println(spent);
}
void printUUID(const char *uuid) {
  lcd.setCursor(0, 0);
  lcd.print(uuid);
  Serial.println(uuid);
}
void printMsg(const char *msg) {
  lcd.setCursor(0, 1);
  lcd.print(msg);
  Serial.println(msg);
}
