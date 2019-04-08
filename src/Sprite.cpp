#include <string>
#include <assert.h>
#include "Sprite.h"
#include "Game.h"
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
    this->texture = nullptr;
}

Sprite::Sprite(GameObject& associated, const std::string &file) : Component(associated) {
    this->texture = nullptr;
    this->Open(file);
}

Sprite::~Sprite() {
    if(this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
    }
}

void Sprite::Open(const std::string &file) {
    if(this->IsOpen()) {
        SDL_DestroyTexture(this->texture);
    }
    this->texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    assert(this->texture != nullptr);
    SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
    this->SetClip(0, 0, this->width, this->height);
}

bool Sprite::IsOpen() {
    return this->texture != nullptr;
}

void Sprite::SetClip(int x, int y, int w, int h) {
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}

void Sprite::Render(float x, float y) {
    if(this->IsOpen()) {
        SDL_Rect dstrect;
        dstrect.x = x;
        dstrect.y = y;
        dstrect.w = this->clipRect.w;
        dstrect.h = this->clipRect.h;
        SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &dstrect);
    }
}

void Sprite::Render() {
    this->Render(this->associated.box.lefUp.x, this->associated.box.lefUp.y);
}

void Sprite::Update(float dt) {
    (void)dt;
}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}

int Sprite::GetWidth() {
    return this->width;
}

int Sprite::GetHeight() {
    return this->height;
}