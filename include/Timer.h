#ifndef TIMER
#define TIMER

class Timer {
public:
    Timer();
    void Update(int dt);
    void Restart();
    int Get();
private:
    int time;
};

#endif