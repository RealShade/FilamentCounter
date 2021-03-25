class Config {
public:
  enum class Options : short { notImplemented = 0 };
  void show();

private:
  void _read();
  void _write();
  Options _option = Options::notImplemented;
};
