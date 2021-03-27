#ifndef DEFINES_H
#define DEFINES_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <SPI.h>

#include "Button.h"
#include "Config.h"
#include "Display.h"
#include "Menu.h"
#include "Optocoupler.h"
#include "Rfid.h"
#include "Spool.h"
#include "Storage.h"

#define PAIR_1_PIN 9
#define PAIR_2_PIN 8
#define RFC_SS_PIN 53
#define RFC_RST_PIN 5
#define BUTTON_PIN 7
#define GEAR_CIRCUMFERENCE 8 * PI
#define DIRECTION -1
#define DIFF_FOR_SAVE 200
#define HOLD_COUNTER 5
#define HOLD_DETECT 500
#define DEBUG_MODE 1

extern LiquidCrystal_I2C lcd;
extern MFRC522 rider;

extern Spool *spool;
extern Config *config;
extern Menu *menu;
extern Display *display;
extern Button *button;
extern Optocoupler *optocoupler;
extern Rfid *rfid;
extern Storage *storage;

#endif
