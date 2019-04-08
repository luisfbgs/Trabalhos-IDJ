#ifndef SOUND
#define SOUND

#include <string>
#include "Component.h"
#include "GameObject.h"

#define INCLUDE_SDL_MIXER
#include<SDL_include.h>

class Sound : public Component {
public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, std::string file);
    void Play(int times = 1);
    void Stop();
    void Open(std::string file);
    bool IsOpen();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
private:
    Mix_Chunk* chunk; 
    int channel;
};

#endif