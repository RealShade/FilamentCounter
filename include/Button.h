class Button {
public:
  enum Mode { holdForConfig = 0, holdForReset = 1 };
  Button();
  void check();
  void show();

private:
  int _prevState = 0;
  unsigned long _pressTimeStart;
  int _clearState = false;
  Mode _mode = Mode::holdForConfig;
  short _counter;
};
