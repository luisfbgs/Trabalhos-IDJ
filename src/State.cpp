#include <memory>
#include "State.h"
#include "Sprite.h"
#include "Sound.h"
#include "GameObject.h"
#include "Face.h"
#include "Common.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"

State::State() {
    this->quitRequested = false;

    std::shared_ptr<GameObject> background(new GameObject());
    std::shared_ptr<Sprite> backgroundSprite(new Sprite(*background, std::string("assets/img/ocean.jpg"), false));
    background->box.lefUp.x = 0;
    background->box.lefUp.y = 0;
    background->box.w = backgroundSprite->GetWidth();
    background->box.h = backgroundSprite->GetHeight();
    
    background->AddComponent(backgroundSprite);

    std::shared_ptr<GameObject> gameTile(new GameObject());   
    std::shared_ptr<Sprite> tileSprite(new Sprite(*gameTile, std::string("assets/img/tileset.png")));
    gameTile->box.lefUp.x = 0;
    gameTile->box.lefUp.y = 0;
    gameTile->box.w = tileSprite->GetWidth();
    gameTile->box.h = tileSprite->GetHeight();

    this->tileSet = std::shared_ptr<TileSet>(new TileSet(64, 64, tileSprite));
    std::shared_ptr<TileMap> tileMap(new TileMap(*gameTile, std::string("assets/map/tileMap.txt"), tileSet));

    gameTile->AddComponent(tileMap);

    this->objectArray.emplace_back(background);
    this->objectArray.emplace_back(gameTile);
    music.Open(std::string("assets/audio/stageState.ogg"));
    music.Play();
}

State::~State() {
    this->objectArray.clear();
}

bool State::QuitRequested() {
    return this->quitRequested;
}

void State::LoadAssets() {

}

void State::Update(int dt) {
    Camera::Update(dt);
    InputManager &input = InputManager::GetInstance();
    this->quitRequested = input.QuitRequested();

    // Create a penguin face if space bar is pressed
    if(input.KeyPress(' ')) {
        int mouseX = input.GetMouseX(), mouseY = input.GetMouseY();
        Vec2 objPos = Vec2(200, 0).Rotate(randReal(0.0f, 360.0f)) + Vec2(mouseX, mouseY);
        this->AddObject((int)objPos.x, (int)objPos.y);
    }

    for(std::shared_ptr<GameObject> object : this->objectArray) {
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

void State::AddObject(int mouseX, int mouseY) {
    std::shared_ptr<GameObject> enemy(new GameObject());
    std::shared_ptr<Sprite> enemySprite(new Sprite(*enemy, std::string("assets/img/penguinface.png")));
    enemy->box.lefUp.x = mouseX;
    enemy->box.lefUp.y = mouseY;
    enemy->box.w = enemySprite->GetWidth();
    enemy->box.h = enemySprite->GetHeight();

    std::shared_ptr<Sound> enemySound(new Sound(*enemy, std::string("assets/audio/boom.wav")));
    enemy->AddComponent(enemySprite);
    enemy->AddComponent(enemySound);
    
    std::shared_ptr<Face> enemyFace(new Face(*enemy));
    enemy->AddComponent(enemyFace);

    this->objectArray.emplace_back(enemy);
}