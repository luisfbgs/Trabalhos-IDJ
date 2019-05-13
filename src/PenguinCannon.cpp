#include <memory>
#include <string>
#include "PenguinCannon.h"
#include "PenguinBody.h"
#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"
#include "Game.h"
#include "Collider.h"

PenguinCannon::PenguinCannon(GameObject& associated) : Component(associated) {
    std::shared_ptr<Sprite> cannonSprite(new Sprite(this->associated, std::string("assets/img/cubngun.png")));
    this->associated.AddComponent(cannonSprite);

    this->angle = 0;
    this->shootCooldown.Update(kShootCooldown);
}

void PenguinCannon::Render() {}

void PenguinCannon::Update(int dt) {
    this->shootCooldown.Update(dt);
    if(PenguinBody::player == nullptr) {
        this->associated.RequestDelete();
    }
    else {
        InputManager& input = InputManager::GetInstance();
        Vec2 direction = {(float)input.GetMouseX(), (float)input.GetMouseY()};
        direction += Camera::pos;
        direction -= this->associated.box.Center();
        this->angle = direction.Angle();
        Sprite *mySprite = dynamic_cast<Sprite*>(this->associated.GetComponent("Sprite").get());
        mySprite->SetAngle(this->angle);
    
        if(this->shootCooldown.Get() >= kShootCooldown && input.IsMouseDown(LEFT_MOUSE_BUTTON)) {
            this->Shoot();
            this->shootCooldown.Restart();
        }
    }
}

bool PenguinCannon::Is(const std::string& type) {
    return type == "PenguinCannon";
}

void PenguinCannon::Shoot() {
    GameObject *bulletGO = new GameObject();

    std::shared_ptr<Bullet> bullet(new Bullet(*bulletGO, this->angle, 0.6, 1, 480, std::string("assets/img/penguinbullet.png"), 4, false));
    bulletGO->AddComponent(bullet);
    Vec2 bulletOffset = {66, 0};
    bulletOffset = bulletOffset.Rotate(angle);
    bulletGO->box.CenterIn(this->associated.box.Center() + bulletOffset);
    
    Game::GetInstance().GetState().AddObject(bulletGO);
}