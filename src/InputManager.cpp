#include <unordered_map>
#include "InputManager.h"

#define INCLUDE_SDL
#include "SDL_include.h"

InputManager::InputManager() {
    this->updateCounter = 0;
    this->quitRequested = false;

}

InputManager::~InputManager() {
    
}

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

void InputManager::Update() {
    SDL_GetMouseState(&this->mouseX, &this->mouseY);
    this->quitRequested = false;
    this->updateCounter++;
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->quitRequested = true;
                break;
            case SDL_MOUSEBUTTONUP:
                this->mouseState[event.button.button] = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                this->mouseState[event.button.button] = true;
                this->mouseUpdate[event.button.button] = this->updateCounter;
                break;
            case SDL_KEYDOWN:
                if(!event.key.repeat) {
                    this->keyState[event.key.keysym.sym] = true;
                    this->keyUpdate[event.key.keysym.sym] = this->updateCounter;
                }
                break;
            case SDL_KEYUP:
                this->keyState[event.key.keysym.sym] = false;
                break;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return this->keyState[key] && this->keyUpdate[key] == this->updateCounter;
}

bool InputManager::KeyRelease(int key) {
    return !this->keyState[key] && this->keyUpdate[key] == this->updateCounter;
}

bool InputManager::IsKeyDown(int key) {
    return this->keyState[key];
}

bool InputManager::MousePress(int button) {
    return this->mouseState[button] && this->mouseUpdate[button] == this->updateCounter;
}

bool InputManager::MouseRelease(int button) {
    return !this->mouseState[button] && this->mouseUpdate[button] == this->updateCounter;
}

bool InputManager::IsMouseDown(int button) {
    return this->mouseState[button];
}

int InputManager::GetMouseX() {
    return this->mouseX;
}

int InputManager::GetMouseY() {
    return this->mouseY;
}

bool InputManager::QuitRequested() {
    return this->quitRequested;
}