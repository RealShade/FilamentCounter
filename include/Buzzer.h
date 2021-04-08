class Buzzer
{
public:
    Buzzer();
    void check();
    void alertStart();
    void alertStop();

private:
    bool _state = false;
    bool _cycleState = false;
    unsigned long _cycleTime = 0;
};
