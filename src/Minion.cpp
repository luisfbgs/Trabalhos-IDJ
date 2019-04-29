#include <memory>
#include <string>
#include <Vec2.h>
#include "Minion.h"
#include "Component.h"
#include "GameObject.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated) {
    this->alienCenter = alienCenter;
    this->arc = arcOffsetDeg;
}

void Minion::Update(int dt) {
    if(!this->alienCenter.lock()) {
        this->associated.RequestDelete();
    }
    else {
        Vec2 pos = {130, 0};
        pos = pos.Rotate(arc);
        pos += this->alienCenter.lock()->box.Center();
        this->associated.box.CenterIn(pos);
        arc += kRotationArc * dt;
    }
}

void Minion::Render() {}

bool Minion::Is(const std::string &type) {
    return type == "Minion";
}

void Minion::Shoot(Vec2 target) {};

void Minion::Start() {
}