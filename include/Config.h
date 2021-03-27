class Config {
public:
  struct Options {
    bool buzzerOn = true;
    bool lcdAlwaysOn = true;
    float direction = -1;
  };
  enum class MenuOptions : short { notImplemented = 0 };
  Config();
  void show();
  void setBuzzerOn(bool isBuzzerOn);
  void setLcdAlwaysOn(bool isLcdAlwaysOn);
  void setDirection(float direction);
  bool isBuzzerOn();
  bool isLcdAlwaysOn();
  float getDirection();

private:
  MenuOptions _menuOption = MenuOptions::notImplemented;
  Options _options;
};
