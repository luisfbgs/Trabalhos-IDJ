#include <string>
#include <assert.h>
#include "Sprite.h"
#include "Game.h"
#include "Camera.h"
#include "Vec2.h"
#include "Resources.h"
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

Sprite::Sprite(GameObject& associated, int frameCount, int frameTime) : Component(associated) {
    this->texture = nullptr;
    this->scale = {1, 1};
    this->angle = 0;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->timeElapsed = 0;
    this->currentFrame = 0;
}

Sprite::Sprite(GameObject& associated, const std::string &file, int frameCount, int frameTime) : Sprite(associated, frameCount, frameTime) {
    this->Open(file);
}

void Sprite::Open(const std::string &file) {
    this->texture = Resources::GetImage(file.c_str());
    assert(this->texture != nullptr);
    SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
    this->width /= this->frameCount;
    this->SetClip(0, 0, this->width, this->height);
    this->associated.box = {this->associated.box.lefUp, (float)this->width, (float)this->height};
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
        x -= Camera::pos.x;
        y -= Camera::pos.y;
        SDL_Rect dstrect;
        dstrect.x = x;
        dstrect.y = y;
        dstrect.w = this->clipRect.w * this->scale.x;
        dstrect.h = this->clipRect.h * this->scale.y;
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture, &this->clipRect, &dstrect, this->angle, nullptr, SDL_FLIP_NONE);
    }
}

void Sprite::Render() {
    this->Render(associated.box.lefUp.x, associated.box.lefUp.y);
}

void Sprite::Update(int dt) {
    this->timeElapsed += dt;
    if(this->timeElapsed > this->frameTime) {
        this->currentFrame++;
        this->currentFrame %= this->frameCount;
    }
    this->SetClip(this->currentFrame * this->width, 0, this->width, this->height);
}

bool Sprite::Is(const std::string &type) {
    return type == "Sprite";
}

int Sprite::GetWidth() {
    return this->width;
}

int Sprite::GetHeight() {
    return this->height;
}

void Sprite::SetScale(float scaleX, float scaleY) {
    this->scale = {scaleX, scaleY};
}

Vec2 Sprite::GetScale() {
    return this->scale;
}

void Sprite::SetAngle(float angle) {
    this->angle = angle;
}

float Sprite::GetAngle() {
    return this->angle;
}

void Sprite::SetFrame(int frame) {
    this->currentFrame = frame;
}

void Sprite::SetFrameCount(int frameCount) {
    this->width *= this->frameCount;
    this->frameCount = frameCount;
    this->width /= this->frameCount;
}