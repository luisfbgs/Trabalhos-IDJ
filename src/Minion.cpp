#include <memory>
#include <string>
#include <Vec2.h>
#include "Minion.h"
#include "Component.h"
#include "GameObject.h"
#include "Game.h"
#include "Bullet.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated) {
    this->alienCenter = alienCenter;
    this->arc = arcOffsetDeg;
}

void Minion::Update(int dt) {
    if(!this->alienCenter.lock()) {
        this->associated.RequestDelete();
    }
    else {
        arc += kRotationArc * dt;
        Sprite *mySprite = dynamic_cast<Sprite*>(this->associated.GetComponent("Sprite").get());
        mySprite->SetAngle(arc);
        Vec2 pos = {150, 0};
        pos = pos.Rotate(arc);
        pos += this->alienCenter.lock()->box.Center();
        this->associated.box.CenterIn(pos);
    }
}

void Minion::Render() {}

bool Minion::Is(const std::string &type) {
    return type == "Minion";
}

void Minion::Shoot(Vec2 target) {
    GameObject *bulletGO = new GameObject();

    float angle = (target - this->associated.box.Center()).Angle();
    std::shared_ptr<Bullet> bullet(new Bullet(*bulletGO, angle, 0.6, 1, 600, std::string("assets/img/minionbullet1.png")));
    bulletGO->box.CenterIn(this->associated.box.Center());
    bulletGO->AddComponent(bullet);

    Game::GetInstance().GetState().AddObject(bulletGO);
};

void Minion::Start() {
}