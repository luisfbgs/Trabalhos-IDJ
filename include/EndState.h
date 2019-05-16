#ifndef ENDSTATE
#define ENDSTATE

#include "State.h"
#include "Music.h"

class EndState : public State {
public:
    EndState();
    ~EndState();
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    void Pause();
    void Resume();

private:
    Music backgroundMusic;
};

#endif