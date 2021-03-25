class Button {
public:
  enum class Mode:short { holdForConfig = 0, holdForReset = 1 };
  Button();
  void check();
  void show();

private:
  int _prevState = 0, _currentState;
  unsigned long _pressTimeStart;
  int _clearState = false;
  Mode _mode = Mode::holdForConfig;
  short _counter;
};
