#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include <assert.h>
#include <string>

#define INCLUDE_SDL
#include "SDL_include.h"
#include "Game.h"
#include "State.h"

Game* Game::instance = nullptr;

Game::Game(const std::string &title, int width, int height) {
    assert(instance == nullptr);
    assert(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER));

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    
    Mix_Init(MIX_INIT_OGG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_AllocateChannels(32);

    instance = this;

    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    this->state = new State();
}   

Game::~Game() {
    delete this->state;
    SDL_DestroyRenderer(Game::renderer);
    SDL_DestroyWindow(Game::window);

    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();

    instance = nullptr;
}

Game& Game::GetInstance() {
	if(instance == nullptr) {
		new Game("Luis Felipe Braga - 16/0071569", 1024, 600);
    }
	return *instance;
}

SDL_Renderer* Game::GetRenderer() {
    return this->renderer;
}

void Game::Run() {
    
    while(!this->state->QuitRequested()){
        this->state->Update(0.0f);
        this->state->Render();
        SDL_RenderPresent(this->renderer);
        SDL_Delay(33);
    }
}