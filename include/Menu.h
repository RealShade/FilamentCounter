class Menu {
public:
  enum class Mode : short {
    waitForFilament,
    spent,
    holdForUnloadSpool,
    unload,
    holdForConfig,
    config,
    holdForReset,
    reset,
    holdForClear,
    clearEEPROM
  };

  Menu();
  void show(int counter = 0);
  void setMode(Mode mode);
  Mode getMode();

private:
  Mode _mode;
};
