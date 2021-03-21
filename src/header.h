#ifndef DEFINES_H
#define DEFINES_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Storage.h"

extern LiquidCrystal_I2C lcd;
extern Storage *st;

extern int PAIR1PIN;
extern int PAIR2PIN;
extern int BUTTONPIN;
extern double ROLLLENGTH;
extern int DIRECTION;

#endif
