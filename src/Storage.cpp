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
  _readOptions();
  _readSpools();
}

// *****************************************************************************

byte Storage::readSpool(SpoolRow *spoolRow)
{
  int idx = -1; // The first spool row with no data

  if (DEBUG_MODE)
  {
    Serial.print("Search spool: ");
    Serial.println(unpackUUIDString(spoolRow->uuid));
  }
  for (int i = 0; i < SPOOL_LIMIT; i++)
  {
    if (_spoolCache[i].hasData == 1)
    {
      if (DEBUG_MODE)
      {
        Serial.print("... compare ");
        Serial.print(unpackUUIDString(_spoolCache[i].uuid));
        Serial.print(" and ");
        Serial.print(unpackUUIDString(spoolRow->uuid));
        Serial.print("... ");
      }
      if (memcmp(&_spoolCache[i].uuid, &spoolRow->uuid, 4) == 0)
      {
        memcpy(spoolRow, &_spoolCache[i], sizeof(SpoolRow));
        Serial.println("found");

        return i;
      }
      if (DEBUG_MODE)
      {
        Serial.println("skip");
      }
    }
    else if (idx == -1)
    {
      idx = i;
    }
  }
  spoolRow->hasData = 1;
  spoolRow->spentInteger = 0;
  spoolRow->spentDecimal = 0;
  memcpy(&_spoolCache[idx], spoolRow, sizeof(SpoolRow));
  if (DEBUG_MODE)
  {
    Serial.print("not found. Created as idx ");
    Serial.println(idx);
  }

  return idx;
}

void Storage::writeOptions()
{
  if (DEBUG_MODE)
  {
    Serial.print("Write options... ");
  }
  EEPROM.put(ADDR_OPTIONS, _packOptions());
  if (DEBUG_MODE)
  {
    Serial.print("done");
  }
}

void Storage::writeSpool(SpoolRow *spoolRow, byte spoolIdx)
{
  if (DEBUG_MODE)
  {
    Serial.print("Write spool ");
    Serial.print(spoolIdx);
    Serial.print("... ");
  }
  memcpy(&_spoolCache[spoolIdx], spoolRow, sizeof(SpoolRow));
  EEPROM.put(_getAddrByIdx(spoolIdx), *spoolRow);
  Serial.println("done");
}

void initEEPROM() { EEPROM.put(ADDR_OPTIONS, 255); }

// *****************************************************************************

void Storage::_readOptions()
{
  byte options;

  if (DEBUG_MODE)
  {
    Serial.print("Read options: ");
  }
  EEPROM.get(0, options);
  Serial.println(options, BIN);

  // If the value of first cell is 255, it means that EEPROM is empty
  if (options == 255)
  {
    _initDefault();
    writeOptions();
  }
  else
  {
    _unpackOptions(options);
  }
}

void Storage::_readSpools()
{
  if (DEBUG_MODE)
  {
    Serial.print("Read spools... ");
  }

  for (int i = 0; i < SPOOL_LIMIT; i++)
  {
    EEPROM.get(_getAddrByIdx(i), _spoolCache[i]);
    if (DEBUG_MODE)
    {
      if (_spoolCache[i].hasData == 1) {
      Serial.print("Found ");
      Serial.println(unpackUUIDString(_spoolCache[i].uuid));
      }
    }
  }
  if (DEBUG_MODE)
  {
    Serial.println("done");
  }
}

void Storage::_initDefault()
{
  if (DEBUG_MODE)
  {
    Serial.println("Init default options");
  }
  _unpackOptions(BIT_BUZZER + BIT_LCD_ALWAYS_ON);
}

void Storage::_unpackOptions(byte options)
{
  config->setBuzzerOn(options & BIT_BUZZER);
  config->setLcdAlwaysOn(options & BIT_LCD_ALWAYS_ON);
  config->setDirection(options & BIT_DIRECTION ? 1 : -1);
}

int Storage::_getAddrByIdx(int idx)
{
  return ADDR_SPOOL_STORAGE_OFFSET + idx * sizeof(SpoolRow);
}

byte Storage::_packOptions()
{
  return static_cast<byte>(config->isBuzzerOn()) * BIT_BUZZER +
         static_cast<byte>(config->isLcdAlwaysOn()) * BIT_LCD_ALWAYS_ON +
         static_cast<byte>(config->getDirection() == 1) * BIT_DIRECTION;
}

void Storage::_clearEEPROM()
{
  if (DEBUG_MODE)
  {
    Serial.print("Clearing EEPROM... ");
  }

  for (unsigned int addr = 0; addr < EEPROM.length(); addr++)
  {
    EEPROM.update(addr, 255);
  }

  if (DEBUG_MODE)
  {
    Serial.println("done");
    _readOptions();
    _readSpools();
  }
}
