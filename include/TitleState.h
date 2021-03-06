#ifndef TITLESTATE
#define TITLESTATE

#include "State.h"
#include "Timer.h"

class TitleState : public State {
public:
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    void Pause();
    void Resume();

private:
    Timer textDelay;
};

#endif