class Endstop
{
public:
    Endstop();
    void check();
    bool isAlarm();
    void resetAlarm();

private:
    int _prevState;
    bool _armed = false;
    bool _alarm = false;
};
