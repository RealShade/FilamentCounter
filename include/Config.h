class Config {
public:
  struct Options {
    bool buzzerOn = true;
    bool lcdAlwaysOn = true;
    double direction = -1;
  };
  enum class MenuOptions : short { notImplemented = 0 };
  Config();
  void show();
  void setBuzzerOn(bool isBuzzerOn);
  void setLcdAlwaysOn(bool isLcdAlwaysOn);
  void setDirection(double direction);
  bool isBuzzerOn();
  bool isLcdAlwaysOn();
  double getDirection();

private:
  MenuOptions _menuOption = MenuOptions::notImplemented;
  Options _options;
};
