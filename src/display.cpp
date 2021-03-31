#include "header.h"

char msg[16];

Display::Display()
{
  if (DEBUG_MODE == 1)
  {
    Serial.println("Display init");
  }
}

// *****************************************************************************

void Display::printUuid()
{
  clear(0);
  printMsg(uuidAsString(spool->getUuid()), 0);
}

// *****************************************************************************

void Display::printSpent()
{
  clear(1);
  dtostrf(spool->getSpent(), 7, 3, msg);
  printMsg(msg, 1);
}

void Display::printHold(const char *text, int counter = 0)
{
  sprintf(msg, "%s%c", text, char(counter));
  printMsg(msg, 1);
}

void Display::clear(short row) { printMsg("                ", row); }

void Display::printMsg(const char *msg, short row = 0)
{
  lcd.setCursor(0, row);
  lcd.print(msg);
  if (DEBUG_MODE == 1)
  {
    Serial.print("LCD: ");
    Serial.println(msg);
  }
}
