class OpticalPair {
public:
  OpticalPair();
  void check();

private:
  int _prevState1;
  int _prevState2;
  int _state1;
  int _state2;
};
