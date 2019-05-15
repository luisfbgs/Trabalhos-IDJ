#include "State.h"

State::State() {
    this->popRequested = false;
    this->quitRequested = false;
    this->started = false;
}

State::~State() {
    this->objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> go_ptr(go);
    
    if(this->started && !go->started) {
        go->Start();
    }

    this->objectArray.emplace_back(go_ptr);
    std::weak_ptr<GameObject> ret(go_ptr);
    return ret;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for(std::shared_ptr<GameObject> object : this->objectArray) {
        if(object.get() == go) {
            return object;
        }
    }
    return std::weak_ptr<GameObject>();
}

bool State::PopRequested() {
    return this->popRequested;
}

bool State::QuitRequested() {
    return this->quitRequested;
}

void State::StartArray() {
    for(int i = 0; i < (int)this->objectArray.size(); i++) {
        std::shared_ptr<GameObject> object = this->objectArray[i];
        object->Start();
    }
    this->started = true;
}

void State::UpdateArray(int dt) {
    for(int i = 0; i < (int)this->objectArray.size(); i++) {
        std::shared_ptr<GameObject> object = this->objectArray[i];
        object->Update(dt);
    }
    
    for(int i = 0; i < (int)this->objectArray.size(); i++) {
        if(this->objectArray[i]->IsDead()) {
            this->objectArray.erase(this->objectArray.begin() + i);
            --i;
        }
    }
}

void State::RenderArray() {
    for(std::shared_ptr<GameObject> object : this->objectArray) {
        object->Render();
    }
}
