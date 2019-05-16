#ifndef MUSIC
#define MUSIC

#include <string>
#include <memory>

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Music {
public:
    Music();
    Music(std::string file);
    ~Music();
    void Play(int times = -1);
    void Stop(int msToStop = 0);
    void Open(std::string file);
    bool IsOpen();

private:
    std::shared_ptr<Mix_Music> music;
};

#endif

