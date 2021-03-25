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
#include "Optical.h"
#include "Rfid.h"
#include "Spool.h"

extern int PAIR_1_PIN;            // Pin for optical pair 1
extern int PAIR_2_PIN;            // Pin for optical pair 1
extern int RFC_RST_PIN;           // RFID rest pin
extern int RFC_SS_PIN;            // RFID selector pin
extern int BUTTON_PIN;            // Pin for button
extern double GEAR_CIRCUMFERENCE; // 8 - diameter of the toothed shaft (mm)
extern int DIRECTION;             // Rotation direction of the toothed shaft
extern double DIFF_FOR_SAVE;      // Differences between previous value, that
                                  // triggered saving the value (mm)
extern int HOLD_COUNTER;          // Half-seconds for counting on hold button
extern unsigned long HOLD_DETECT; // Milliseconds for detect holding button

extern LiquidCrystal_I2C lcd;
extern MFRC522 rider;

extern Spool *spool;
extern Config config;
extern Menu menu;
extern Display display;
extern Button button;
extern OpticalPair opticalPair;
extern Rfid rfid;

#endif
