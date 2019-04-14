#include <string>
#include "Face.h"
#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "Common.h"
#include "InputManager.h"

Face::Face(GameObject& associated) : Component(associated) {
    this->hitpoints = 30;
}

void Face::Damage(int damage) {
    hitpoints -= damage;
    if(hitpoints <= 0) {
        Sound* sound = (Sound*)this->associated.GetComponent("Sound").get();
        if(sound != nullptr) {
            sound->Play();
        }
        this->associated.RequestDelete();
    }
}

void Face::Update(float dt) {
    (void)dt;
    InputManager &input = InputManager::GetInstance();
    if(input.MousePress(LEFT_MOUSE_BUTTON)) {
        int mouseX = input.GetMouseX(), mouseY = input.GetMouseY();
        if(this->associated.box.Contains(mouseX, mouseY)) {
            this->Damage(randInt(10, 19));
        }
    }
}

void Face::Render() {}

bool Face::Is(std::string type) {
    return type == "Face";
}