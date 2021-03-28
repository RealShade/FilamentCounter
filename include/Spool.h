#ifndef DEFSPOOL
#define DEFSPOOL

#include <Arduino.h>

const char *unpackUUIDString(byte _uuid[4]);

class Spool
{
public:
  Spool(byte uuid[4]);
  byte *getUUID();
  void getUUID(byte uuid[4]);
  double getSpent();
  void incSpent(double diff);
  void write();
  void reset();

private:
  void _read();

  byte _uuid[4];
  double _spent = 0;
  double _spentLastSave = 0;
  byte _spoolIdx;
};

#endif
