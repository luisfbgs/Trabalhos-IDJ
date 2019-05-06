#include <string>
#include "Collider.h"
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated) {
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(int dt) {
    this->box = this->associated.box;
    this->box.w *= this->scale.x;
    this->box.h *= this->scale.y;
    this->box.CenterIn(this->associated.box.Center() + this->offset);
}

bool Collider::Is(const std::string& type) {
    return type == "Collider";
}

void Collider::Render() {}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}
