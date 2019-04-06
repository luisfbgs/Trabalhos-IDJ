#include <Music.h>
#define INCLUDE_SDL_MIXER
#include <SDL_include.h>

Music::Music() {
    this->music = nullptr;
}

Music::Music(std::string file) {
    this->music = nullptr;
    this->Open(file);
}

Music::~Music() {
    if(this->IsOpen()) {
        this->Stop(0);
        Mix_FreeMusic(music);
    }
}

void Music::Play(int times) {
    if(this->IsOpen()) {
        Mix_PlayMusic(music, times);
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    if(this->IsOpen()) {
        this->Stop(0);
        Mix_FreeMusic(music);
    }
    this->music = Mix_LoadMUS(file.c_str());
}

bool Music::IsOpen() {
    return this->music != nullptr;
}