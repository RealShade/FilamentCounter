class Optocoupler {
public:
  Optocoupler();
  void check();

private:
  int _prevState1;
  int _prevState2;
};
