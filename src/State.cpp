#include <memory>
#include "State.h"
#include "Sprite.h"
#include "Sound.h"
#include "GameObject.h"
#include "Common.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "Alien.h"
#include "CameraFollower.h"

State::State() {
    this->quitRequested = false;
    this->started = false;
}

State::~State() {
    this->objectArray.clear();
}

bool State::QuitRequested() {
    return this->quitRequested;
}

void State::LoadAssets() {
    GameObject* background = new GameObject();
    std::shared_ptr<Sprite> backgroundSprite(new Sprite(*background, std::string("assets/img/ocean.jpg")));
    background->box.lefUp.x = 0;
    background->box.lefUp.y = 0;
    background->box.w = backgroundSprite->GetWidth();
    background->box.h = backgroundSprite->GetHeight();
    std::shared_ptr<CameraFollower> cameraFollower(new CameraFollower(*background));
    
    background->AddComponent(backgroundSprite);
    background->AddComponent(cameraFollower);

    GameObject* gameTile = new GameObject();   
    std::shared_ptr<Sprite> tileSprite(new Sprite(*gameTile, std::string("assets/img/tileset.png")));
    gameTile->box.lefUp.x = 0;
    gameTile->box.lefUp.y = 0;
    gameTile->box.w = tileSprite->GetWidth();
    gameTile->box.h = tileSprite->GetHeight();

    this->tileSet = std::shared_ptr<TileSet>(new TileSet(64, 64, tileSprite));
    std::shared_ptr<TileMap> tileMap(new TileMap(*gameTile, std::string("assets/map/tileMap.txt"), tileSet));

    gameTile->AddComponent(tileMap);

    GameObject* alienGO = new GameObject();

    std::shared_ptr<Alien> alien(new Alien(*alienGO, 10));
    alienGO->AddComponent(alien);

    alienGO->box.CenterIn({512, 300});
    
    this->AddObject(background);
    this->AddObject(gameTile);
    this->AddObject(alienGO);
    music.Open(std::string("assets/audio/stageState.ogg"));
    music.Play();
}

void State::Update(int dt) {
    Camera::Update(dt);
    InputManager &input = InputManager::GetInstance();
    this->quitRequested = input.QuitRequested();

    for(int i = 0; i < (int)this->objectArray.size(); i++) {
        std::shared_ptr<GameObject> object = this->objectArray[i];
        object->Update(dt);
    }
    
    for(int i = 0; i < (int)this->objectArray.size(); i++) {
        if(this->objectArray[i]->IsDead()) {
            this->objectArray.erase(this->objectArray.begin() + i);
            --i;
        }
    }
}

void State::Render() {
    for(std::shared_ptr<GameObject> object : this->objectArray) {
        object->Render();
    }
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> go_ptr(go);
    
    if(this->started && !go->started) {
        go->Start();
    }

    this->objectArray.emplace_back(go_ptr);
    std::weak_ptr<GameObject> ret(go_ptr);
    return ret;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for(std::shared_ptr<GameObject> object : this->objectArray) {
        if(object.get() == go) {
            return object;
        }
    }
    return std::weak_ptr<GameObject>();
}

void State::Start() {
    this->LoadAssets();
    for(int i = 0; i < (int)this->objectArray.size(); i++) {
        std::shared_ptr<GameObject> object = this->objectArray[i];
        object->Start();
    }
    this->started = true;
}