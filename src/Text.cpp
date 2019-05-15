#include <string>
#include "Text.h"
#include "Component.h"
#include "GameObject.h"
#include "Game.h"

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) : Component(associated) {
    this->texture = nullptr;
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;
    this->RemakeTexture();
    this->font = nullptr;
}

Text::~Text() {
    if(this->texture != nullptr){
        SDL_DestroyTexture(this->texture);
    }
}

void Text::Update(int dt) {
    (void)dt;
}

void Text::Render() {
    SDL_Rect clipRect;
    clipRect.x = clipRect.y = 0;
    clipRect.w = this->associated.box.w;
    clipRect.h = this->associated.box.h;
    SDL_Rect dstrect;
    dstrect.x = this->associated.box.lefUp.x;
    dstrect.y = this->associated.box.lefUp.y;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &dstrect, 0, nullptr, SDL_FLIP_NONE);
}

bool Text::Is(const std::string& type) {
    return type == "Text";
}

void Text::SetText(std::string text) {
    this->text = text;
    this->RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    this->RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    this->RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
    this->fontFile = fontFile;
    this->RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    this->RemakeTexture();
}

void Text::RemakeTexture() {

}