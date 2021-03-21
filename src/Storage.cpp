#include "display.h"
#include "header.h"

Storage::Storage(const char *uuid) {
  _uuid = uuid;
  _read();
}
const char *Storage::getUUID() { return _uuid; }
double Storage::getSpent() { return _spent; }
void Storage::incSpent(double diff) { _spent += (DIRECTION * diff); }
void Storage::write() {}
void Storage::_read() { _spent = 11.34518; }
