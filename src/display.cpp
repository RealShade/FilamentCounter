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

void Display::printUUID()
{
  clear(0);
  printMsg(unpackUUIDString(spool->getUUID()), 0);
}

// *****************************************************************************

void Display::printSpent()
{
  dtostrf(spool->getSpent(), 7, 3, msg);
  clear(1);
  printMsg(msg, 1);
}

void Display::printHold(const char *text, int counter = 0)
{
  clear(1);
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
