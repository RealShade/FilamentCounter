#include "header.h"
#include <EEPROM.h>

// void (*resetFunc)(void) = 0;

// *****************************************************************************

Storage::Storage()
{
  if (DEBUG_MODE)
  {
    Serial.println("Storage init");
    Serial.print("EEPROM size: ");
    Serial.println(EEPROM.length());
    Serial.print("Limit spools: ");
    Serial.println(SPOOL_LIMIT);
  }
}

// *****************************************************************************

byte Storage::readSpool(SpoolRow *spoolRow)
{
  SpoolRow temp;
  int idx = -1; // The first spool row with no data

  if (DEBUG_MODE)
  {
    Serial.print("Search spool: ");
    Serial.println(uuidAsString(spoolRow->uuid));
  }
  for (int i = 0; i < SPOOL_LIMIT; i++)
  {
    EEPROM.get(_getAddrByIdx(i), temp);
    if (temp.hasData == 1)
    {
      if (DEBUG_MODE)
      {
        Serial.print("... compare ");
        Serial.print(uuidAsString(temp.uuid));
        Serial.print(" and ");
        Serial.print(uuidAsString(spoolRow->uuid));
        Serial.print("... ");
      }
      if (temp.uuid == spoolRow->uuid)
      {
        if (DEBUG_MODE)
          Serial.println("found");
        memcpy(spoolRow, &temp, sizeof(SpoolRow));

        return i;
      }
      if (DEBUG_MODE)
        Serial.println("skip");
    }
    else if (idx == -1)
      idx = i;
  }
  // If reach this point, then UUID is not found
  spoolRow->hasData = 1;
  spoolRow->spentInteger = 0;
  spoolRow->spentDecimal = 0;
  if (DEBUG_MODE)
  {
    Serial.print("not found. Created as idx ");
    Serial.println(idx);
  }

  return idx;
}

byte Storage::readOptions()
{
  byte options;

  if (DEBUG_MODE)
    Serial.print("Read options: ");
  EEPROM.get(0, options);

  return options;
}

void Storage::writeOptions(byte options)
{
  if (DEBUG_MODE)
    Serial.print("Write options... ");
  EEPROM.put(ADDR_OPTIONS, options);
  if (DEBUG_MODE)
    Serial.println("done");
}

void Storage::writeSpool(SpoolRow *spoolRow, byte spoolIdx)
{
  if (DEBUG_MODE)
  {
    Serial.print("Write spool ");
    Serial.print(spoolIdx);
    Serial.print("... ");
  }
  EEPROM.put(_getAddrByIdx(spoolIdx), spoolRow);
  Serial.println("done");
}

void Storage::clearEEPROM()
{
  if (DEBUG_MODE)
    Serial.print("Clearing EEPROM... ");

  for (unsigned int addr = 0; addr < EEPROM.length(); addr++)
    EEPROM.update(addr, 255);

  if (DEBUG_MODE)
    Serial.println("done");
}

// *****************************************************************************

int Storage::_getAddrByIdx(int idx)
{
  return ADDR_SPOOL_STORAGE_OFFSET + idx * sizeof(SpoolRow);
}
