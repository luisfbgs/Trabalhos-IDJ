#include "Camera.h"
#include "GameObject.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Game.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos(0, 0);
Vec2 Camera::speed(0, 0);

void Camera::Follow(GameObject* newFocus) {
    Camera::focus = newFocus;
}

void Camera::Unfollow() {
    Camera::focus = nullptr;
}

void Camera::Update(int dt) {
    if(focus != nullptr) {
        Game& game = Game::GetInstance();
        Camera::pos = focus->box.Center() - Vec2(game.GetWidth() / 2.0f, game.GetHeight() / 2.0f);
    }
    else {
        InputManager &input = InputManager::GetInstance();
        int up = input.IsKeyDown('w');
        int down = input.IsKeyDown('s');
        int left = input.IsKeyDown('a');
        int right = input.IsKeyDown('d');
        Vec2 deltaPos(right - left, down - up);
        if(deltaPos.Length() != 0) {
            deltaPos = deltaPos.Norm();
            deltaPos.x *= speed.x;
            deltaPos.y *= speed.y;
            deltaPos = deltaPos * dt;
        }
        Camera::pos += deltaPos;
    }
}