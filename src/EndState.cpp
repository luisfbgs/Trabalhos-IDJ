#include <memory>
#include <string>
#include "EndState.h"
#include "GameData.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Game.h"
#include "Music.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include "Text.h"

EndState::EndState() {
    GameObject* bgGO = new GameObject();
    
    std::shared_ptr<Sprite> bgSprite;
    if(GameData::playerVictory) {
        bgSprite = std::shared_ptr<Sprite>(new Sprite(*bgGO, std::string("assets/img/win.jpg")));
        backgroundMusic.Open(std::string("assets/audio/endStateWin.ogg"));
    }
    else {
        bgSprite = std::shared_ptr<Sprite>(new Sprite(*bgGO, std::string("assets/img/lose.jpg")));
        backgroundMusic.Open(std::string("assets/audio/endStateLose.ogg"));
    }
    bgSprite->SetScale((float)Game::GetInstance().GetWidth() / bgSprite->GetWidth(), (float)Game::GetInstance().GetHeight() / bgSprite->GetHeight());    
    std::shared_ptr<CameraFollower> cameraFollower(new CameraFollower(*bgGO));
    bgGO->AddComponent(bgSprite);
    bgGO->AddComponent(cameraFollower);

    this->AddObject(bgGO);

    GameObject *pressESCGO = new GameObject();
    std::shared_ptr<Text> pressESCtext(new Text(*pressESCGO, std::string("assets/font/Call me maybe.ttf"), 50, Text::TextStyle::SOLID, std::string("Pressione ESC para sair"), {0, 0, 0, 0}));
    pressESCGO->AddComponent(pressESCtext);
    pressESCGO->box.CenterIn({Game::GetInstance().GetWidth() / 1.92f, 5.8f * Game::GetInstance().GetHeight() / 7});

    this->AddObject(pressESCGO);

    GameObject *pressSpaceGO = new GameObject();
    std::shared_ptr<Text> pressSpaceText(new Text(*pressSpaceGO, std::string("assets/font/Call me maybe.ttf"), 50, Text::TextStyle::SOLID, std::string("Pressione Espaco para jogar novamente"), {0, 0, 0, 0}));
    pressSpaceGO->AddComponent(pressSpaceText);
    pressSpaceGO->box.CenterIn({Game::GetInstance().GetWidth() / 1.92f, 6.3f * Game::GetInstance().GetHeight() / 7});

    this->AddObject(pressSpaceGO);
}


EndState::~EndState() {}

void EndState::LoadAssets() {}

void EndState::Update(int dt) {
    (void)dt;
    this->UpdateArray(dt);
    InputManager &input = InputManager::GetInstance();
    this->quitRequested = input.KeyPress(' ');
    GameData::quitAll = input.QuitRequested() || input.KeyPress(ESCAPE_KEY);
}

void EndState::Render() {
    this->RenderArray();
}

void EndState::Start() {
    this->backgroundMusic.Play();
}

void EndState::Pause() {}

void EndState::Resume() {}