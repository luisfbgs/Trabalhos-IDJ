#include <string>
#include <unordered_map>
#include "Resources.h"
#include "Game.h"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

Resources::~Resources() {
    ClearImages();
    ClearMusics();
    ClearSounds();
}

SDL_Texture* Resources::GetImage(std::string file) {
    if(!imageTable.count(file)){
        imageTable[file] = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    }
    return imageTable[file];
}

void Resources::ClearImages() {
    for(std::pair<std::string, SDL_Texture*> texture : imageTable){
        SDL_DestroyTexture(texture.second);
    }
}

Mix_Music* Resources::GetMusic(std::string file) {
    if(!musicTable.count(file)){
        musicTable[file] = Mix_LoadMUS(file.c_str());
    }
    return musicTable[file];
}

void Resources::ClearMusics() {
    for(std::pair<std::string, Mix_Music*> music : musicTable){
        Mix_FreeMusic(music.second);
    }
}

Mix_Chunk* Resources::GetSound(std::string file) {
    if(!soundTable.count(file)){
        soundTable[file] = Mix_LoadWAV(file.c_str());
    }
    return soundTable[file];
}

void Resources::ClearSounds() {
    for(std::pair<std::string, Mix_Chunk*> sound : soundTable){
        Mix_FreeChunk(sound.second);
    }
}