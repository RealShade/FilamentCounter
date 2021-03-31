class Display {
public:
  Display();
  void printUuid();
  void printSpent();
  void printHold(const char *text, int counter);
  void clear(short row);
  void printMsg(const char *uuid, short row);
};
