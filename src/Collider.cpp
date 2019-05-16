#include <string>
#include <SDL2/SDL.h>
#include "Collider.h"
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Camera.h"
#include "Game.h"
//#define DEBUG

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated) {
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(int dt) {
    (void)dt;
    this->box = this->associated.box;
    this->box.w *= this->scale.x;
    this->box.h *= this->scale.y;
    this->box.CenterIn(this->associated.box.Center() + this->offset);
}

bool Collider::Is(const std::string& type) {
    return type == "Collider";
}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center(this->box.Center());
	SDL_Point points[5];

	Vec2 point = (this->box.lefUp - center).Rotate(this->associated.GetAngle())
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(this->box.lefUp.x + this->box.w, this->box.lefUp.y) - center).Rotate(this->associated.GetAngle())
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(this->box.lefUp.x + this->box.w, this->box.lefUp.y + this->box.h) - center).Rotate(this->associated.GetAngle())
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(this->box.lefUp.x, this->box.lefUp.y + this->box.h) - center).Rotate(this->associated.GetAngle())
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}


void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}
