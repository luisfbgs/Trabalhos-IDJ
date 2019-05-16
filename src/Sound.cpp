#include<string>
#include "Sound.h"
#include "GameObject.h"
#include "Resources.h"

Sound::Sound(GameObject& associated) : Component(associated) {
    this->chunk = nullptr;
    this->channel = -1;
}

Sound::Sound(GameObject& associated, std::string file) : Sound(associated) {
    this->Open(file);
}

void Sound::Play(int times) {
    if(this->chunk != nullptr && this->channel == -1) {
        this->channel = Mix_PlayChannel(-1, this->chunk.get(), times - 1);
    }
}

void Sound::Stop() {
    if(this->channel != -1) {
        Mix_HaltChannel(this->channel);
        this->channel = -1;
    }
}

void Sound::Open(std::string file) {
    this->chunk = Resources::GetSound(file.c_str());
}

bool Sound::IsOpen() {
    return this->chunk != nullptr;
}

void Sound::Update(int dt) {
    (void)dt;
}

void Sound::Render() {}

bool Sound::Is(const std::string &type) {
    return type == "Sound";
}