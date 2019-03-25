#include "State.h"

State::State() {
    quitRequested = false;

    this->bg.Open("assets/img/ocean.jpg");
    this->music.Open("assets/audio/stageState.ogg");
    this->music.Play();
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {

}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    this->bg.Render(0, 0);
}