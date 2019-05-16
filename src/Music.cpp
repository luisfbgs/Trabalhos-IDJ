#include "Music.h"
#include "Resources.h"
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

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
    }
}

void Music::Play(int times) {
    if(this->IsOpen()) {
        Mix_PlayMusic(this->music.get(), times);
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    if(this->IsOpen()) {
        this->Stop();
    }
    this->music = Resources::GetMusic(file.c_str());
}

bool Music::IsOpen() {
    return this->music != nullptr;
}