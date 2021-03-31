#include "header.h"

char uuidString[8];

const char *uuidAsString(unsigned long uuid)
{

  sprintf(uuidString, "%08lX", uuid);

  return uuidString;
}

// *****************************************************************************

Spool::Spool(unsigned long uuid)
{
  _uuid = uuid;
  if (DEBUG_MODE == 1)
  {
    Serial.print("Spool init: ");
    Serial.println(uuidAsString(uuid));
  }
  _read();
}

// *****************************************************************************

unsigned long Spool::getUuid() { return _uuid; }

void Spool::getUuid(unsigned long uuid) { uuid = _uuid; }

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
  spoolRow.uuid = _uuid;
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
  
  spoolRow.uuid = _uuid;
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
