#include <memory>
#include "StageState.h"
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
#include "PenguinBody.h"
#include "Collision.h"
#include "Rect.h"
#include "Resources.h"
#include "Game.h"
#include "State.h"
#include "GameData.h"
#include "EndState.h"
#include "Common.h"

void StageState::LoadAssets() {
    GameObject* background = new GameObject();
    std::shared_ptr<Sprite> backgroundSprite(new Sprite(*background, std::string("assets/img/ocean.jpg")));
    backgroundSprite->SetScale((float)Game::GetInstance().GetWidth() / backgroundSprite->GetWidth(), (float)Game::GetInstance().GetHeight() / backgroundSprite->GetHeight());
    std::shared_ptr<CameraFollower> cameraFollower(new CameraFollower(*background));
    
    background->AddComponent(backgroundSprite);
    background->AddComponent(cameraFollower);
    this->AddObject(background);

    GameObject* gameTile = new GameObject();   
    std::shared_ptr<Sprite> tileSprite(new Sprite(*gameTile, std::string("assets/img/tileset.png")));
    gameTile->box.lefUp.x = 0;
    gameTile->box.lefUp.y = 0;
    gameTile->box.w = tileSprite->GetWidth();
    gameTile->box.h = tileSprite->GetHeight();

    this->tileSet = std::shared_ptr<TileSet>(new TileSet(64, 64, tileSprite));
    std::shared_ptr<TileMap> tileMap(new TileMap(*gameTile, std::string("assets/map/tileMap.txt"), tileSet));

    gameTile->AddComponent(tileMap);
    this->AddObject(gameTile);

    for(int i = 0; i < 4; i++) {
        GameObject* alienGO = new GameObject();

        std::shared_ptr<Alien> alien(new Alien(*alienGO, 6));
        alienGO->AddComponent(alien);

        alienGO->box.CenterIn({randReal(0, 1480), randReal(0, 1280)});
        this->AddObject(alienGO);
    }

    GameObject* penguinGO = new GameObject();

    std::shared_ptr<PenguinBody> penguin(new PenguinBody(*penguinGO));
    penguinGO->AddComponent(penguin);

    penguinGO->box.lefUp = {704, 640};
    this->AddObject(penguinGO);

    Camera::Follow(penguinGO);

    music.Open(std::string("assets/audio/stageState.ogg"));
    music.Play();
}

void StageState::Update(int dt) {
    Camera::Update(dt);
    InputManager &input = InputManager::GetInstance();
    this->quitRequested = input.KeyPress(ESCAPE_KEY);
    GameData::quitAll = input.QuitRequested();

    this->UpdateArray(dt);

    for(int i = 0; i < (int)this->objectArray.size(); i++) {
        std::shared_ptr<GameObject> object1 = this->objectArray[i];
        if(object1->GetComponent("Collider") != nullptr) {
            for(int j = i + 1; j < (int)this->objectArray.size(); j++) {
                std::shared_ptr<GameObject> object2 = this->objectArray[j];
                if(object2->GetComponent("Collider") != nullptr) {
                    Rect rect1 = object1->box;
                    Rect rect2 = object2->box;
                    if(Collision::IsColliding(rect1, rect2, object1->GetAngle(), object2->GetAngle())) {
                        object1->NotifyCollision(*object2);    
                        object2->NotifyCollision(*object1);    
                    }
                }
            }
        }
    }

    if(Alien::alienCount == 0) {
        GameData::playerVictory = true;
        Game::GetInstance().Push(new EndState());
    }
    if(PenguinBody::player == nullptr) {
        GameData::playerVictory = false;
        Game::GetInstance().Push(new EndState());
    }
}

void StageState::Render() {
    TileMap *tileMap = nullptr;
    
    for(std::shared_ptr<GameObject> object : this->objectArray) {
        object->Render();

        if(tileMap == nullptr) {
            Component *aux = object->GetComponent("TileMap").get();
            if(aux != nullptr) {
                tileMap = dynamic_cast<TileMap*>(aux);
            }
        }
    }

    if(tileMap != nullptr) {
        tileMap->RenderLayer(1);
    }
}

std::weak_ptr<GameObject> StageState::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> go_ptr(go);
    
    if(this->started && !go->started) {
        go->Start();
    }

    this->objectArray.emplace_back(go_ptr);
    std::weak_ptr<GameObject> ret(go_ptr);
    return ret;
}

std::weak_ptr<GameObject> StageState::GetObjectPtr(GameObject* go) {
    for(std::shared_ptr<GameObject> object : this->objectArray) {
        if(object.get() == go) {
            return object;
        }
    }
    return std::weak_ptr<GameObject>();
}

void StageState::Start() {
    GameData::playerVictory = false;
    this->LoadAssets();
    this->StartArray();
}

void StageState::Pause() {
    this->music.Stop(0);
}

void StageState::Resume() {
    this->objectArray.clear();
    this->started = false;
    GameData::playerVictory = false;
    this->LoadAssets();
    this->StartArray();
}