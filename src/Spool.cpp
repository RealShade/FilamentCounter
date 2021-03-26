#include "header.h"

char uuid[9];

Spool::Spool(unsigned char uuid[4]) {
  memcpy(_uuid, uuid, 4);
  _read();
}

const unsigned char *Spool::getUUID() { return _uuid; }
const char *Spool::getUUIDString() {
  for (byte j = 0; j < 4; j++) {
    sprintf(uuid, "%x%x%x%x", spool->getUUID()[0], spool->getUUID()[1],
            spool->getUUID()[2], spool->getUUID()[3]);
  }
  return uuid;
}

double Spool::getSpent() { return _spent; }

void Spool::incSpent(double diff) {
  _spent += (DIRECTION * diff);
  if (abs(_spent - _spentLastSave) >= DIFF_FOR_SAVE) {
    spool->write();
  }
}

void Spool::write() {}

void Spool::reset() {
  _spent = 0;
  write();
}

void Spool::_read() { _spent = 11.34518; }
