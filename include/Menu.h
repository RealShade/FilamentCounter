class Menu {
public:
  enum class Mode : short {
    waitForFilament = 0,
    spent = 1,
    holdForConfig = 2,
    config = 3,
    holdForReset = 4,
    reset = 5,
    holdForClear = 6,
    clearEEPROM = 7
  };

  Menu();
  void show(int counter = 0);
  void setMode(Mode mode);
  Mode getMode();

private:
  Mode _mode;
};
