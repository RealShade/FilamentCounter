class Endstop
{
public:
    Endstop();
    void check();
    bool isAlert();
    void resetAlert();

private:
    int _prevState = -1;
    bool _armed = false;
    bool _alert = false;
};
