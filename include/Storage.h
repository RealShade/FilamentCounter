#include <Arduino.h>

#define ADDR_OPTIONS 0
#define ADDR_SPOOL_STORAGE_OFFSET 10
#define SPOOL_MAX 255
#define SPOOL_LIMIT \
  min(SPOOL_MAX, (int)((EEPROM.length() - ADDR_SPOOL_STORAGE_OFFSET) / sizeof(SpoolRow)))
#define BIT_BUZZER 1
#define BIT_LCD_ALWAYS_ON 2
#define BIT_DIRECTION 4

// *****************************************************************************

class Storage
{
public:
  struct SpoolRow
  {
    byte hasData; // 1 - has data, everything else - empty
    byte uuid[4];
    int spentInteger;
    byte spentDecimal;
  };

  Storage();

  byte readSpool(SpoolRow *spoolRow);

  void writeOptions();
  void writeSpool(SpoolRow *spoolRow, byte spoolIdx);

  void clearEEPROM();

private:
  void _readOptions();
  void _readSpools();
  void _unpackOptions(byte options);
  byte _packOptions();
  int _getAddrByIdx(int idx);

  SpoolRow *_spoolCache = new SpoolRow[SPOOL_MAX];
};
