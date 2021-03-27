#include "header.h"
#include <EEPROM.h>

#define ADDR_CONFIG 0
#define ADDR_SPOOL_COUNT 1
#define ADDR_SPOOL_STORAGE 10

// *****************************************************************************

Storage::Storage() {
  if (DEBUG_MODE) {
    Serial.println("Storage init");
  }
  _readOptions();
}

// *****************************************************************************

void Storage::readSpool(SpoolRow *spoolRow) {
  SpoolRow *temp;
  if (DEBUG_MODE) {
    Serial.print("Search spool: ");
    Serial.print(unpackUUIDString(spoolRow->uuid));
    Serial.print("... ");
  }
  for (int i = 0; i < _spoolCount; i++) {
    EEPROM.get(ADDR_SPOOL_STORAGE + i * sizeof(*spoolRow), temp);
    if (temp->uuid == spoolRow->uuid) {
      memcpy(spoolRow, temp, sizeof(*spoolRow));
      Serial.println("found");
      return;
    }
  }
  spoolRow->spent = 0;
  Serial.println("not found");
}

void Storage::writeOptions() {
  // EEPROM.put(ADDR_CONFIG, _packOptions());
  // EEPROM.put(ADDR_SPOOL_COUNT, _spoolCount);
}

void Storage::writeSpool(SpoolRow *spoolRow) {
  SpoolRow *temp;
  int addr;
  Serial.print(_spoolCount);
  if (DEBUG_MODE) {
    Serial.print("Search spool... ");
  }
  // @TODO maybe there is need a function for find the UUID and return the
  // address in EEPROM
  for (int i = 0; i < _spoolCount; i++) {
    addr = ADDR_SPOOL_STORAGE + i * sizeof(*spoolRow);
    EEPROM.get(addr, temp);
    if (temp->uuid == spoolRow->uuid) {
      Serial.print("found. Writing... ");
      // EEPROM.put(addr, spoolRow);
      Serial.println("done");
      return;
    }
  }
  Serial.print("not found. Creating... ");
  addr = addr + sizeof(*spoolRow);
  // EEPROM.put(addr, spoolRow);
  Serial.println("done");
}

// *****************************************************************************

void Storage::_readOptions() {
  byte options;

  if (DEBUG_MODE) {
    Serial.print("Read options: ");
  }
  EEPROM.get(0, options);
  Serial.println(options, BIN);

  // If the value of first cell is 255, it means that EEPROM is unitialized
  if (options == 255) {
    _initDefault();
  } else {
    _unpackOptions(options);
    EEPROM.get(1, _spoolCount);
  }
  Serial.print("Spool count: ");
  Serial.println(_spoolCount);
}

void Storage::_initDefault() {
  if (DEBUG_MODE) {
    Serial.println("Init default options");
  }
  _spoolCount = 0;
  _unpackOptions(1 + 2);
}

void Storage::_unpackOptions(byte options) {
  config->setBuzzerOn(options & 1);
  config->setLcdAlwaysOn(options & 2);
  config->setDirection(options & 4 ? 1 : -1);
}

byte Storage::_packOptions() {
  return static_cast<byte>(config->isBuzzerOn()) +
         static_cast<byte>(config->isLcdAlwaysOn()) * 2 +
         static_cast<byte>(config->getDirection() == 1) * 4;
}
