#include "header.h"

void Config::show() {
  switch (_option) {
  case Options::notImplemented:
    display.printMsg("Not implemented", 1);
    break;
  }
}

void Config::_read() {}

void Config::_write() {}
