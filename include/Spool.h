#ifndef DEFSPOOL
#define DEFSPOOL

#include <Arduino.h>

const char *uuidAsString(unsigned long uuid);

class Spool
{
public:
  Spool(unsigned long uuid);
  unsigned long getUuid();
  void getUuid(unsigned long uuid);
  double getSpent();
  void incSpent(double diff);
  void write();
  void reset();

private:
  void _read();

  unsigned long _uuid;
  double _spent = 0, _spentLastSave = 0;
  byte _spoolIdx; // Index of spool in EEPROM struct (not EEPROM address!)
};

#endif
