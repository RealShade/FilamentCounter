#include "Spool.h"
#include <Arduino.h>

class Storage {
public:
  struct SpoolRow {
    byte uuid[4];
    float spent = 0;
  };
  Storage();

  void readSpool(SpoolRow *spoolRow);

  void writeOptions();
  void writeSpool(SpoolRow *spoolRow);

private:
  void _initDefault();
  void _readOptions();
  void _unpackOptions(byte options);
  byte _packOptions();

  byte _spoolCount;
};
