#include <string>
#include "Bullet.h"
#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "Common.h"
#include "Collider.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frames, bool targetsPlayer) : Component(associated) {
    std::shared_ptr<Sprite> bulletSprite (new Sprite(this->associated, sprite, frames, 150));
    bulletSprite->SetAngle(angle);
    bulletSprite->SetScale(1.5f, 1.5f);
    this->associated.AddComponent(bulletSprite);

    std::shared_ptr<Collider> bulletCollider (new Collider(this->associated));
    this->associated.AddComponent(bulletCollider);

    this->distanceLeft = maxDistance;
    this->speed = {1, 0};
    this->speed = this->speed.Rotate(angle);
    this->speed *= speed;
    this->damage = damage;
    this->targetsPlayer = targetsPlayer;
}

void Bullet::Update(int dt) {
    Vec2 move = speed * dt;
    if(move.Length() > this->distanceLeft) {
        move = move.Norm();
        move *= this->distanceLeft;
    }
    this->associated.box.lefUp += move;
    this->distanceLeft -= move.Length();
    if(equals(this->distanceLeft, 0)) {
        this->associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(const std::string &type) {
    return type == "Bullet";
}

int Bullet::GetDamage() {
    return this->damage;
}

void Bullet::NotifyCollision(GameObject& other) {
    if(other.GetComponent("Alien") != nullptr && !this->targetsPlayer) {
        this->associated.RequestDelete();
    }
    else if(other.GetComponent("PenguinBody") != nullptr && this->targetsPlayer) {
        this->associated.RequestDelete();
    }
}