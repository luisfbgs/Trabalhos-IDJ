#include <algorithm>
#include <memory>
#include <string>
#include "GameObject.h"

GameObject::GameObject() {
    this->isDead = false;
}

GameObject::~GameObject() {
    this->components.clear();
}

void GameObject::Update(float dt) {
    for(std::shared_ptr<Component> component : this->components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for(std::shared_ptr<Component> component : this->components) {
        component->Render();
    }
}

bool GameObject::IsDead() {
    return this->isDead;
}

void GameObject::RequestDelete() {
    this->isDead = true;
}

void GameObject::AddComponent(std::shared_ptr<Component> cpt) {
    this->components.emplace_back(cpt);
}

void GameObject::RemoveComponent(std::shared_ptr<Component> cpt) {
    std::vector<std::shared_ptr<Component>>::iterator it;
    it = std::find(this->components.begin(), this->components.end(), cpt);

    if(it != this->components.end()) {
        this->components.erase(it);
    }
}

std::shared_ptr<Component> GameObject::GetComponent(std::string type) {
    for(std::shared_ptr<Component> component : this->components) {
        if(component->Is(type)) {
            return component;
        }
    }
    return nullptr;
}