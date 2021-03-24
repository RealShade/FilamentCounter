#include "header.h"

Spool::Spool(const char *uuid) {
  _uuid = uuid;
  _read();
}

const char *Spool::getUUID() { return _uuid; }
double Spool::getSpent() { return _spent; }

void Spool::incSpent(double diff) { _spent += (DIRECTION * diff); }
void Spool::write() {}

void Spool::_read() { _spent = 11.34518; }
