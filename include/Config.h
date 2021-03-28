class Config
{
public:
  struct Options
  {
    bool buzzerOn = true;
    bool lcdAlwaysOn = true;
    double direction = -1;
  };
  enum class MenuOptions : short
  {
    buzzer = 0,
    lcdAlwaysOn = 1,
    direction = 2,
    exit = 3
  };
  Config();
  void show(int counter = -1);
  void setBuzzerOn(bool isBuzzerOn);
  void setLcdAlwaysOn(bool isLcdAlwaysOn);
  void setDirection(double direction);
  bool isBuzzerOn();
  bool isLcdAlwaysOn();
  double getDirection();
  void nextOption();
  void showHold(int counter);
  void changeOption();

private:
  MenuOptions _menuOption = MenuOptions::buzzer;
  Options _options;
};
