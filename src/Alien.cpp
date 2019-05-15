#include <memory>
#include <queue>
#include "Alien.h"
#include "Component.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Camera.h"
#include "GameObject.h"
#include "Minion.h"
#include "Game.h"
#include "Common.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"
#include "PenguinBody.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
    std::shared_ptr<Sprite> alienSprite(new Sprite(this->associated, "assets/img/alien.png"));
    this->associated.AddComponent(alienSprite);

    std::shared_ptr<Collider> alienCollider (new Collider(this->associated));
    this->associated.AddComponent(alienCollider);

    this->nMinions = nMinions;
    this->hp = 10;
    alienCount++;
    this->state = AlienState::RESTING;
}

Alien::~Alien() {
    this->minionArray.clear();
    alienCount--;
}

void Alien::Start() {
    if(this->nMinions) {
        std::weak_ptr<GameObject> myPtr = Game::GetInstance().GetCurrentState().GetObjectPtr(&this->associated);
        float arc = 360.0 / this->nMinions;
        for(int i = 0; i < this->nMinions; i++) {
            GameObject *minionGO = new GameObject();

            std::shared_ptr<Minion> minion(new Minion(*minionGO, myPtr, arc * i));
            std::shared_ptr<Sprite> minionSprite(new Sprite(*minionGO, "assets/img/minion.png"));
            minionSprite->SetScale(randReal(1.0f, 1.5f), randReal(1.0f, 1.5f));

            minionGO->AddComponent(minion);
            minionGO->AddComponent(minionSprite);

            std::weak_ptr<GameObject> newMinion;
            newMinion = Game::GetInstance().GetCurrentState().AddObject(minionGO);
            this->minionArray.push_back(newMinion);
        }
    }
}

void Alien::Update(int dt) {
    Sprite *mySprite = dynamic_cast<Sprite*>(this->associated.GetComponent("Sprite").get());
    mySprite->SetAngle(mySprite->GetAngle() - 0.09 * dt);
    
    if(PenguinBody::player != nullptr) {
        if(this->state == AlienState::RESTING) {
            this->restTimer.Update(dt);
            if(this->restTimer.Get() >= kAlienCooldown) {
                this->destination = PenguinBody::player->GetPosition();
                this->speed = this->destination - this->associated.box.Center();
                this->speed = this->speed.Norm();
                this->state = AlienState::MOVING;
                this->restTimer.Restart();
            }
        }
        else {
            if(this->destination.Dist(this->associated.box.Center()) <= 400) {
                this->Shoot(PenguinBody::player->GetPosition());
                this->state = AlienState::RESTING;
            }
            else {
                this->associated.box.lefUp += this->speed * dt; 
            }
        }
    }

    if(this->hp <= 0) {
        GameObject *deathGO = new GameObject();
        std::shared_ptr<Sprite> deathSprite(new Sprite(*deathGO, std::string("assets/img/aliendeath.png"), 4, 200, 800));
        std::shared_ptr<Sound> deathSound(new Sound(*deathGO, std::string("assets/audio/boom.wav")));
        deathGO->AddComponent(deathSprite);
        deathGO->AddComponent(deathSound);
        deathSound->Play();
        deathGO->box.CenterIn(this->associated.box.Center());
        Game::GetInstance().GetCurrentState().AddObject(deathGO);
        this->associated.RequestDelete();
    }
}   

void Alien::Render() {}

bool Alien::Is(const std::string &type) {
    return type == "Alien";
}

void Alien::NotifyCollision(GameObject& other) {
    if(other.GetComponent("Bullet") != nullptr) {
        Bullet* bullet = dynamic_cast<Bullet*>(other.GetComponent("Bullet").get());
        if(!bullet->targetsPlayer) {
            this->hp -= bullet->GetDamage();
        }
    }
}

void Alien::Shoot(Vec2 target) {
    int id = 0;
    float minDist = this->minionArray[0].lock()->box.Center().Dist(target);
    for(int i = 1; i < this->nMinions; i++) {
        if(this->minionArray[i].lock()->box.Center().Dist(target) < minDist) {
            id = i;
            minDist = this->minionArray[i].lock()->box.Center().Dist(target);
        }
    }
    Minion *shooter = dynamic_cast<Minion*>(this->minionArray[id].lock()->GetComponent("Minion").get());
    shooter->Shoot(target);
}