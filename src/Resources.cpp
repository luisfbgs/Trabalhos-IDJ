#include <string>
#include <unordered_map>
#include <memory>
#include "Resources.h"
#include "Game.h"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

Resources::~Resources() {
    ClearImages();
    ClearMusics();
    ClearSounds();
    ClearFonts();
}

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    auto deleter = [](SDL_Texture* texture) {
        SDL_DestroyTexture(texture);
    };
    if(!imageTable.count(file)){
        imageTable[file] = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str()), deleter);
    }
    return imageTable[file];
}

void Resources::ClearImages() {
    imageTable.clear();
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
    auto deleter = [](Mix_Music* music) {
        Mix_FreeMusic(music);
    };
    if(!musicTable.count(file)){
        musicTable[file] = std::shared_ptr<Mix_Music>(Mix_LoadMUS(file.c_str()), deleter);
    }
    return musicTable[file];
}

void Resources::ClearMusics() {
    musicTable.clear();
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
    auto deleter = [](Mix_Chunk* sound) {
        Mix_FreeChunk(sound);
    };
    if(!soundTable.count(file)){
        soundTable[file] = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(file.c_str()), deleter);
    }
    return soundTable[file];
}

void Resources::ClearSounds() {
    soundTable.clear();
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int size) {
    auto deleter = [](TTF_Font* font) {
        TTF_CloseFont(font);
    };
    if(!fontTable.count(file + std::to_string(size))){
        fontTable[file+ std::to_string(size)] = std::shared_ptr<TTF_Font>(TTF_OpenFont(file.c_str(), size), deleter);
    }
    return fontTable[file + std::to_string(size)];
}

void Resources::ClearFonts() {
    fontTable.clear();
}

void Resources::Free() {
    auto texture = imageTable.begin();
    while(texture != imageTable.end()){
        if(texture->second.unique()) {
            texture = imageTable.erase(texture);
        }
        else {
            texture++;
        }
    }

    auto music = musicTable.begin();
    while(music != musicTable.end()){
        if(music->second.unique()) {
            music = musicTable.erase(music);
        }
        else {
            music++;
        }
    }

    auto sound = soundTable.begin();
    while(sound != soundTable.end()){
        if(sound->second.unique()) {
            sound = soundTable.erase(sound);
        }
        else {
            sound++;
        }
    }
    
    auto font = fontTable.begin();
    while(font != fontTable.end()){
        if(font->second.unique()) {
            font = fontTable.erase(font);
        }
        else {
            font++;
        }
    }
}