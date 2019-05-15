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

void TitleState::Update(int dt) {
    (void)dt;
    InputManager &input = InputManager::GetInstance();
    this->quitRequested = input.KeyPress(ESCAPE_KEY) || input.QuitRequested();
    if(!this->quitRequested && input.KeyPress(' ')) {
        Game::GetInstance().Push(new StageState());
    }
}

void TitleState::LoadAssets() {
    GameObject *titleGO = new GameObject();
    std::shared_ptr<Sprite> titleSprite(new Sprite(*titleGO, std::string("assets/img/title.jpg")));
    titleSprite->SetScale((float)Game::GetInstance().GetWidth() / titleSprite->GetWidth(), (float)Game::GetInstance().GetHeight() / titleSprite->GetHeight());    
    std::shared_ptr<CameraFollower> cameraFollower(new CameraFollower(*titleGO));
    titleGO->AddComponent(titleSprite);
    titleGO->AddComponent(cameraFollower);
    this->AddObject(titleGO);
}

void TitleState::Render() {
    this->RenderArray();
}

void TitleState::Start() {
    this->LoadAssets();
    this->UpdateArray(0);
}

void TitleState::Pause() {}

void TitleState::Resume() {
    this->UpdateArray(0);
}