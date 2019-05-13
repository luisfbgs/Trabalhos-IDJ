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
#include "Common.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
    std::shared_ptr<Sprite> alienSprite(new Sprite(this->associated, "assets/img/alien.png"));
    this->associated.AddComponent(alienSprite);

    std::shared_ptr<Collider> alienCollider (new Collider(this->associated));
    this->associated.AddComponent(alienCollider);

    this->nMinions = nMinions;
    this->hp = 10;
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
            minionSprite->SetScale(randReal(1.0f, 1.5f), randReal(1.0f, 1.5f));

            minionGO->AddComponent(minion);
            minionGO->AddComponent(minionSprite);

            std::weak_ptr<GameObject> newMinion;
            newMinion = Game::GetInstance().GetState().AddObject(minionGO);
            this->minionArray.push_back(newMinion);
        }
    }
}

void Alien::Update(int dt) {
    Sprite *mySprite = dynamic_cast<Sprite*>(this->associated.GetComponent("Sprite").get());
    mySprite->SetAngle(mySprite->GetAngle() - 0.09 * dt);
        
    InputManager &input = InputManager::GetInstance();
    if(input.MousePress(RIGHT_MOUSE_BUTTON)) {
        Alien::Action nAction(Action::ActionType::MOVE, input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);
        this->taskQueue.push(nAction);
    }
    if(input.MousePress(LEFT_MOUSE_BUTTON)) {
        Alien::Action nAction(Action::ActionType::SHOOT, input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);
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
            int id = 0;
            float minDist = minionArray[0].lock()->box.Center().Dist(doIt.pos);
            for(int i = 1; i < nMinions; i++) {
                if(minionArray[i].lock()->box.Center().Dist(doIt.pos) < minDist) {
                    id = i;
                    minDist = minionArray[i].lock()->box.Center().Dist(doIt.pos);
                }
            }
            Minion *shooter = dynamic_cast<Minion*>(minionArray[id].lock()->GetComponent("Minion").get());
            shooter->Shoot(doIt.pos);
            taskQueue.pop();
        }
    }
    if(this->hp <= 0) {
        GameObject *deathGO = new GameObject();
        std::shared_ptr<Sprite> deathSprite(new Sprite(*deathGO, std::string("assets/img/aliendeath.png"), 4, 200, 800));
        std::shared_ptr<Sound> deathSound(new Sound(*deathGO, std::string("assets/audio/boom.wav")));
        deathGO->AddComponent(deathSprite);
        deathGO->AddComponent(deathSound);
        deathSound->Play();
        deathGO->box.CenterIn(this->associated.box.Center());
        Game::GetInstance().GetState().AddObject(deathGO);
        this->associated.RequestDelete();
    }
}   

void Alien::Render() {}

bool Alien::Is(const std::string &type) {
    return type == "Alien";
}

void Alien::NotifyCollision(GameObject& other) {
    if(other.GetComponent("Bullet") != nullptr) {
        Bullet* bullet = dynamic_cast<Bullet*>(other.GetComponent("Bullet").get());
        if(!bullet->targetsPlayer) {
            this->hp -= bullet->GetDamage();
        }
    }
}

Alien::Action::Action(ActionType type, float x, float y) {
    this->type = type;
    this->pos = {x, y};
}