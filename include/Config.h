#define BIT_BUZZER 1
#define BIT_LCD_ALWAYS_ON 2
#define BIT_DIRECTION 4
#define BIT_ENDSTOP 8

class Config
{
public:
  struct Options
  {
    bool buzzerOn = true;
    bool lcdAlwaysOn = true;
    double direction = -1;
    bool endstop = true;
  };
  enum class MenuOptions : short
  {
    buzzer,
    lcdAlwaysOn,
    direction,
    endstop,
    exit
  };
  Config();
  void show(int counter = -1);
  bool isBuzzerOn();
  bool isLcdAlwaysOn();
  double getDirection();
  bool isEndstopOn();
  void nextOption();
  void showHold(int counter);
  void holdedOption();

private:
  void _setBuzzerOn(bool isBuzzerOn);
  void _setLcdAlwaysOn(bool isLcdAlwaysOn);
  void _setDirection(double direction);
  void _setEndstopOn(bool isEndstopOn);
  void _unpackOptions(byte options);
  byte _packOptions();
  MenuOptions _menuOption = MenuOptions::buzzer;
  Options _options;
};
