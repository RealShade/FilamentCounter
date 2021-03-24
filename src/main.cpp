#include "header.h"

int PAIR_1_PIN = 9;
int PAIR_2_PIN = 8;
int RFC_RST_PIN = 10;
int RFC_SS_PIN = 11;
int BUTTON_PIN = 7;
double GEAR_CIRCUMFERENCE = 8 * PI;
int DIRECTION = -1;
double DIFF_FOR_SAVE = 200;
int HOLD_COUNTER = 5;
unsigned long HOLD_DETECT = 500;

LiquidCrystal_I2C lcd(0x27, 16, 2);

Spool spool = NULL;
Config config = Config();
Menu menu = Menu();
Display display = Display();
Button button = Button();

byte charWait[5][8] = {
    {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000},
    {0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000},
    {0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100},
    {0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110},
    {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111}};

double spentLastSave = 0; // Last saved value;

void setup() {
  menu.setMode(Menu::waitForFilament);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  for (int i = 0; i < 5; i++) {
    lcd.createChar(i, charWait[i]);
  }

  setupPair();

  menu.show();
}

void loop() {
  loopPair();
  button.check();
  if (abs(spool.getSpent() - spentLastSave) >= DIFF_FOR_SAVE) {
    spool.write();
  }
}
