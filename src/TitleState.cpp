#include <memory>
#include <string>
#include "TitleState.h"
#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Text.h"
#include "Timer.h"

void TitleState::Update(int dt) {
    (void)dt;
    InputManager &input = InputManager::GetInstance();
    this->quitRequested = input.KeyPress(ESCAPE_KEY) || input.QuitRequested();
    if(!this->quitRequested && input.KeyPress(' ')) {
        Game::GetInstance().Push(new StageState());
    }
    textDelay.Update(dt);
}

void TitleState::LoadAssets() {
    GameObject *bgGO = new GameObject();
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, std::string("assets/img/title.jpg")));
    bgSprite->SetScale((float)Game::GetInstance().GetWidth() / bgSprite->GetWidth(), (float)Game::GetInstance().GetHeight() / bgSprite->GetHeight());    
    std::shared_ptr<CameraFollower> cameraFollower(new CameraFollower(*bgGO));
    bgGO->AddComponent(bgSprite);
    bgGO->AddComponent(cameraFollower);
    this->AddObject(bgGO);

    GameObject *pressSpaceGO = new GameObject();
    SDL_Color color = {0, 0, 0, 0};
    std::shared_ptr<Text> pressSpaceText(new Text(*pressSpaceGO, std::string("assets/font/Call me maybe.ttf"), 140, Text::TextStyle::SOLID, std::string("Pressione Espaco"), color));
    pressSpaceGO->AddComponent(pressSpaceText);
    pressSpaceGO->box.CenterIn({Game::GetInstance().GetWidth() / 1.92f, 5.8f * Game::GetInstance().GetHeight() / 7});

    this->AddObject(pressSpaceGO);
}

void TitleState::Render() {
    (*this->objectArray.begin())->Render();
    if(textDelay.Get() <= 600) {
        (*std::next(this->objectArray.begin()))->Render();
    }
    else if(textDelay.Get() >= 1000) {
        textDelay.Update(-1000);
    }
}

void TitleState::Start() {
    this->LoadAssets();
    this->UpdateArray(0);
}

void TitleState::Pause() {}

void TitleState::Resume() {
    this->UpdateArray(0);
}