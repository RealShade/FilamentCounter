#include "header.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rider(RFC_SS_PIN, RFC_RST_PIN);

Spool *spool = NULL;
Config *config = NULL;
Menu *menu = NULL;
Display *display = NULL;
Button *button = NULL;
Optocoupler *optocoupler = NULL;
Rfid *rfid = NULL;
Storage *storage = NULL;

byte charWait[5][8] = {
    {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000},
    {0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000},
    {0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100},
    {0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110},
    {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111}};

void setup() {
  SPI.begin();
  if (DEBUG_MODE == 1) {
    Serial.begin(9600);
    Serial.println("Application start");
  }

  if (DEBUG_MODE == 1) {
    Serial.print("LCD init... ");
  }
  lcd.init();
  lcd.backlight();
  lcd.clear();
  if (DEBUG_MODE == 1) {
    Serial.println("done");
  }

  for (int i = 0; i < 5; i++) {
    lcd.createChar(i, charWait[i]);
  }

  config = new Config();
  menu = new Menu();
  display = new Display();
  button = new Button();
  optocoupler = new Optocoupler();
  storage = new Storage();
  rfid = new Rfid();

  menu->setMode(Menu::Mode::waitForFilament);
}

void loop() {
  button->check();
  rfid->check();
  if (spool != NULL) {
    optocoupler->check();
  }
}
