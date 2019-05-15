#include <memory>
#include <string>
#include <algorithm>
#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Sprite.h"
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Game.h"
#include "InputManager.h"
#include "Collider.h"
#include "Bullet.h"
#include "Camera.h"
#include "Sound.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
    player = this;

    std::shared_ptr<Sprite> bodySprite (new Sprite(this->associated, std::string("assets/img/penguin.png"), 1, 100));
    this->associated.AddComponent(bodySprite);

    std::shared_ptr<Collider> bodyCollider (new Collider(this->associated));
    this->associated.AddComponent(bodyCollider);

    this->angle = 0;
    this->hp = 10;
    this->linearSpeed = 0;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
    Camera::Unfollow();
}

void PenguinBody::Start() {
    GameObject* cannonGO = new GameObject();
    std::shared_ptr<PenguinCannon> cannon(new PenguinCannon(*cannonGO));
    cannonGO->AddComponent(cannon);

    pcannon = Game::GetInstance().GetCurrentState().AddObject(cannonGO);
}

void PenguinBody::Update(int dt) {
    InputManager& input = InputManager::GetInstance();

    if(input.IsKeyDown('w')) {
        this->linearSpeed = std::min(1.0f, this->linearSpeed + dt / 1000.0f);
    }
    if(input.IsKeyDown('s')) {
        this->linearSpeed = std::max(0.0f, this->linearSpeed - dt / 600.0f);
    }
    if(input.IsKeyDown('a')) {
        this->angle -= dt / 3.0f;
        this->angle += 360 * (this->angle <= -360);
    }
    if(input.IsKeyDown('d')) {
        this->angle += dt / 3.0f;
        this->angle -= 360 * (this->angle >= 360);
    }

    Sprite *mySprite = dynamic_cast<Sprite*>(this->associated.GetComponent("Sprite").get());
    mySprite->SetAngle(this->angle);
    
    this->speed = Vec2(1, 0).Rotate(angle);
    this->speed *= this->linearSpeed * dt;
    this->associated.box.CenterIn(this->associated.box.Center() + this->speed);
    pcannon.lock()->box.CenterIn(this->associated.box.Center());

    if(this->hp <= 0) {
        GameObject *deathGO = new GameObject();
        std::shared_ptr<Sprite> deathSprite(new Sprite(*deathGO, std::string("assets/img/penguindeath.png"), 5, 150, 750));
        std::shared_ptr<Sound> deathSound(new Sound(*deathGO, std::string("assets/audio/boom.wav")));
        deathGO->AddComponent(deathSprite);
        deathGO->AddComponent(deathSound);
        deathSound->Play();
        deathGO->box.CenterIn(this->associated.box.Center());
        Game::GetInstance().GetCurrentState().AddObject(deathGO);
        this->associated.RequestDelete();
    }
}

void PenguinBody::Render() {}

bool PenguinBody::Is(const std::string& type) {
    return type == "PenguinBody";
}

void PenguinBody::NotifyCollision(GameObject& other) {
    if(other.GetComponent("Bullet") != nullptr) {
        Bullet* bullet = dynamic_cast<Bullet*>(other.GetComponent("Bullet").get());
        if(bullet->targetsPlayer) {
            this->hp -= bullet->GetDamage();
        }
    }
}

Vec2 PenguinBody::GetPosition() {
    return this->associated.box.Center();
}