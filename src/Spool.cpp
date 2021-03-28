#include "header.h"

char uuid[9];

const char *unpackUUIDString(byte _uuid[4])
{
  for (byte j = 0; j < 4; j++)
  {
    sprintf(uuid, "%X%X%X%X", _uuid[0], _uuid[1], _uuid[2], _uuid[3]);
  }
  return uuid;
}

// *****************************************************************************

Spool::Spool(byte uuid[4])
{
  memcpy(_uuid, uuid, 4);
  if (DEBUG_MODE == 1)
  {
    Serial.print("Spool init: ");
    Serial.print(_uuid[0], HEX);
    Serial.print(_uuid[1], HEX);
    Serial.print(_uuid[2], HEX);
    Serial.println(_uuid[3], HEX);
  }
  _read();
}

// *****************************************************************************

byte *Spool::getUUID() { return _uuid; }

void Spool::getUUID(byte uuid[4]) { uuid = _uuid; }

double Spool::getSpent() { return _spent; }

void Spool::incSpent(double diff)
{
  _spent += (static_cast<double>(DIRECTION) * diff);
  if (abs(_spent - _spentLastSave) >= DIFF_FOR_SAVE)
  {
    spool->write();
  }
  if (DEBUG_MODE == 1)
  {
    Serial.print("Change spent by counter: ");
    Serial.println(_spent);
  }
}

void Spool::write()
{
  Storage::SpoolRow spoolRow;
  spoolRow.hasData = 1;
  memcpy(spoolRow.uuid, _uuid, 4);
  spoolRow.spentInteger = static_cast<int>(_spent);
  spoolRow.spentDecimal = static_cast<int>((_spent - spoolRow.spentInteger) * 100);
  storage->writeSpool(&spoolRow, _spoolIdx);
}

void Spool::reset()
{
  if (DEBUG_MODE == 1)
  {
    Serial.println("Reset spent");
  }
  _spent = 0;
  write();
}

// *****************************************************************************

void Spool::_read()
{
  Storage::SpoolRow spoolRow;
  memcpy(spoolRow.uuid, _uuid, 4);
  _spoolIdx = storage->readSpool(&spoolRow);
  _spent = static_cast<double>(spoolRow.spentInteger) + (static_cast<double>(spoolRow.spentDecimal) / 100);
  if (DEBUG_MODE == 1)
  {
    Serial.print("Set loaded spent: ");
    Serial.print(_spent);
    Serial.print(", idx:  ");
    Serial.println(_spoolIdx);
  }
}
