#include <memory>
#include <string>
#include <Vec2.h>
#include "Minion.h"
#include "Component.h"
#include "GameObject.h"
#include "Game.h"
#include "Bullet.h"
#include "Collider.h"
#include "Sprite.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated) {
    this->alienCenter = alienCenter;
    this->arc = arcOffsetDeg;

    std::shared_ptr<Collider> alienCollider (new Collider(this->associated));
    this->associated.AddComponent(alienCollider);
}

void Minion::Update(int dt) {
    if(!this->alienCenter.lock()) {
        GameObject *deathGO = new GameObject();
        std::shared_ptr<Sprite> deathSprite(new Sprite(*deathGO, std::string("assets/img/aliendeath.png"), 4, 200, 800));
        deathSprite->SetScale(0.5f, 0.5f);
        deathGO->AddComponent(deathSprite);
        deathGO->box.CenterIn(this->associated.box.Center());
        Game::GetInstance().GetCurrentState().AddObject(deathGO);
        this->associated.RequestDelete();
    }
    else {
        arc += kRotationArc * dt;
        Sprite *mySprite = dynamic_cast<Sprite*>(this->associated.GetComponent("Sprite").get());
        mySprite->SetAngle(arc);
        Vec2 pos = {200, 0};
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
    std::shared_ptr<Bullet> bullet(new Bullet(*bulletGO, angle, 1, 1, 480, std::string("assets/img/minionbullet2.png"), 3));
    bulletGO->box.CenterIn(this->associated.box.Center());
    bulletGO->AddComponent(bullet);

    Game::GetInstance().GetCurrentState().AddObject(bulletGO);
};

void Minion::Start() {
}
