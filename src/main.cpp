#include "button.h"
#include "display.h"
#include "header.h"
#include "optical.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Storage *st;

int PAIR1PIN = 9;           // Pin for optical pair 1
int PAIR2PIN = 8;           // Pin for optical pair 1
int BUTTONPIN = 7;          // Pin for button
double ROLLLENGTH = 8 * PI; // 8 - diameter of the toothed shaft (mm)
int DIRECTION = -1;         // Rotation direction of the toothed shaft
double DIFFFORSAVE = 200; // Differences between previous value, that triggered
                          // saving the value (mm)

double spentLastSave = 0; // Last saved value;

void setup() {
  Serial.begin(9600);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.clear();
  setupPair();
  setupButton();
  st = new Storage("1234567890");
  printUUID(st->getUUID());
  printSpent(st->getSpent());
}

void loop() {
  loopPair();
  loopButton();
  if (abs(st->getSpent() - spentLastSave) >= DIFFFORSAVE) {
    st->write();
  }
}
