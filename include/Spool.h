class Spool {
public:
  Spool(unsigned char uuid[4]);
  const unsigned char *getUUID();
  const char *getUUIDString();
  double getSpent();
  void incSpent(double diff);
  void write();
  void reset();

private:
  void _read();
  unsigned char _uuid[4];
  double _spent = 0;
  double _spentLastSave = 0;
};
