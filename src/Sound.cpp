#include<string>
#include "Sound.h"
#include "GameObject.h"

Sound::Sound(GameObject& associated) : Component(associated) {
    this->chunk = nullptr;
    this->channel = -1;
}

Sound::Sound(GameObject& associated, std::string file) : Sound(associated) {
    this->Open(file);
}

Sound::~Sound() {
    if(this->channel != -1) {
        while(Mix_Playing(this->channel));
    }
    if(this->chunk != nullptr) {
        this->Stop();
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times) {
    if(this->chunk != nullptr && this->channel == -1) {
        this->channel = Mix_PlayChannel(-1, this->chunk, times - 1);
    }
}

void Sound::Stop() {
    if(this->channel != -1) {
        Mix_HaltChannel(this->channel);
        this->channel = -1;
    }
}

void Sound::Open(std::string file) {
    this->chunk = Mix_LoadWAV(file.c_str());
}

bool Sound::IsOpen() {
    return this->chunk != nullptr;
}

void Sound::Update(float dt) {
    (void)dt;
}

void Sound::Render() {}

bool Sound::Is(std::string type) {
    return type == "Sound";
}