#include <memory>
#include <queue>
#include "Alien.h"
#include "Component.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Camera.h"
#include "GameObject.h"
#include "Minion.h"
#include "Game.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
    std::shared_ptr<Sprite> alienSprite(new Sprite(this->associated, "assets/img/alien.png"));
    this->associated.AddComponent(alienSprite);
    this->nMinions = nMinions;
}

Alien::~Alien() {
    this->minionArray.clear();
}

void Alien::Start() {
    if(this->nMinions) {
        std::weak_ptr<GameObject> myPtr = Game::GetInstance().GetState().GetObjectPtr(&this->associated);
        float arc = 360.0 / this->nMinions;
        for(int i = 0; i < this->nMinions; i++) {
            GameObject *minionGO = new GameObject();

            std::shared_ptr<Minion> minion(new Minion(*minionGO, myPtr, arc * i));
            std::shared_ptr<Sprite> minionSprite(new Sprite(*minionGO, "assets/img/minion.png"));

            minionGO->AddComponent(minion);
            minionGO->AddComponent(minionSprite);

            std::weak_ptr<GameObject> newMinion;
            newMinion = Game::GetInstance().GetState().AddObject(minionGO);
            this->minionArray.push_back(newMinion);
        }
    }
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