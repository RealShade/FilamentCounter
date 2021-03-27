#ifndef DEFSPOOL
#define DEFSPOOL

#include <Arduino.h>

const char *unpackUUIDString(byte _uuid[4]);

class Spool {
public:
  Spool(byte uuid[4]);
  byte *getUUID();
  void getUUID(byte uuid[4]);
  float getSpent();
  void setSpent(float spent);
  void incSpent(double diff);
  void write();
  void reset();

private:
  void _read();
  byte _uuid[4];
  float _spent = 0;
  float _spentLastSave = 0;
};

#endif
