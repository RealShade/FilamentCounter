class Buzzer
{
public:
    enum class Mode : byte
    {
        off,
        click,
        alarm,
    };

    Buzzer();
    void check();
    void alarmStart();
    void clickStart();
    void buzzerOff();

private:
    bool _state = false;
    unsigned long _timeStart = 0;
    Mode _mode = Mode::off;
};
