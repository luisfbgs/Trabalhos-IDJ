#include <memory>
#include "Alien.h"
#include "Sprite.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
    std::shared_ptr<Sprite> alienSprite(new Sprite(this->associated, "assets/img/alien.png"));
    this->associated.AddComponent(alienSprite);
}

Alien::~Alien() {
    this->minionArray.clear();
}

void Alien::Start() {

}

void Alien::Update(int dt) {
    
}