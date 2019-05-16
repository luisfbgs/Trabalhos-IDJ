#ifndef SOUND
#define SOUND

#include <string>
#include <memory>
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
    void Update(int dt);
    void Render();
    bool Is(const std::string &type);
private:
    std::shared_ptr<Mix_Chunk> chunk; 
    int channel;
};

#endif