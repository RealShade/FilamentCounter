#include "header.h"

Spool::Spool(const char *uuid) {
  _uuid = uuid;
  _read();
}

const char *Spool::getUUID() { return _uuid; }

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
