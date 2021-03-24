class Spool {
public:
  Spool(const char *uuid);
  const char *getUUID();
  double getSpent();
  void incSpent(double diff);
  void write();

private:
  void _read();
  const char *_uuid;
  double _spent = 0;
};
