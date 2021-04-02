#include <Arduino.h>

#define ADDR_OPTIONS 0
#define ADDR_SPOOL_STORAGE_OFFSET 10
#define SPOOL_MAX 255
#define SPOOL_LIMIT \
  min(SPOOL_MAX, (int)((EEPROM.length() - ADDR_SPOOL_STORAGE_OFFSET) / sizeof(SpoolRow)))

// *****************************************************************************

class Storage
{
public:
  struct SpoolRow
  {
    byte hasData; // 1 - has data, everything else - empty
    unsigned long uuid;
    unsigned int spentInteger;
    byte spentDecimal;
  };

  Storage();

  byte readSpool(SpoolRow *spoolRow);
  void writeSpool(SpoolRow *spoolRow, byte spoolIdx);

  byte readOptions();
  void writeOptions(byte options);

  void clearEEPROM();

private:
  int _getAddrByIdx(int idx);
};
