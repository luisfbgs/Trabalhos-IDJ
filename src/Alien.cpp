#include <memory>
#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Camera.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
    std::shared_ptr<Sprite> alienSprite(new Sprite(this->associated, "assets/img/alien.png"));
    this->associated.AddComponent(alienSprite);
}

Alien::~Alien() {
    this->minionArray.clear();
}

void Alien::Start() {

}

void Alien::Update(int dt) {
    InputManager &input = InputManager::GetInstance();
    if(input.MousePress(RIGHT_MOUSE_BUTTON)) {
        Alien::Action nAction(Action::ActionType::MOVE, input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);
        this->taskQueue.push(nAction);
    }
    if(input.MousePress(LEFT_MOUSE_BUTTON)) {
        Alien::Action nAction(Action::ActionType::SHOOT, input.GetMouseX(), input.GetMouseY());
        this->taskQueue.push(nAction);
    }
    if(!this->taskQueue.empty()) {
        Alien::Action doIt = this->taskQueue.front();
        if(doIt.type == Action::ActionType::MOVE) {
            if(doIt.pos.Dist(this->associated.box.Center()) < dt) {
                this->associated.box.CenterIn(doIt.pos);
                taskQueue.pop();
            }
            else {
                Vec2 move = doIt.pos - this->associated.box.Center();
                move = move.Norm() * dt;
                this->associated.box.lefUp += move; 
            }
        }
        else if(doIt.type == Action::ActionType::SHOOT) {
            taskQueue.pop();
        }
    }
}   

void Alien::Render() {}

bool Alien::Is(const std::string &type) {
    return type == "Alien";
}

Alien::Action::Action(ActionType type, float x, float y) {
    this->type = type;
    this->pos = {x, y};
}