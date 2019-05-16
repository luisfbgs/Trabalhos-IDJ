#include <assert.h>
#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "InputManager.h"
#include "Game.h"
#include "State.h"
#include "Camera.h"
#include "Resources.h"
#include "GameData.h"

Game* Game::instance = nullptr;

Game::Game(const std::string &title, int width, int height) {
    assert(instance == nullptr);
    assert(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER));

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    
    Mix_Init(MIX_INIT_OGG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_AllocateChannels(32);

    TTF_Init();

    instance = this;

    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    this->storedState = nullptr;
    this->dt = 0;
    this->frameStart = 0;
    this->width = width;
    this->height = height;
}   

Game::~Game() {
    if(this->storedState != nullptr) {
        delete this->storedState;
    }

    TTF_Quit();
    SDL_DestroyRenderer(Game::renderer);
    SDL_DestroyWindow(Game::window);

    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();

    instance = nullptr;
}

Game& Game::GetInstance() {
	if(instance == nullptr) {
		new Game("Luis Felipe Braga - 16/0071569", 1600, 900);
    }
	return *instance;
}

SDL_Renderer* Game::GetRenderer() {
    return this->renderer;
}

void Game::Run() {
    Camera::speed = {0.7f, 0.7f};
    InputManager &input = InputManager::GetInstance();
    this->stateStack.push(std::unique_ptr<State>(this->storedState));
    this->storedState = nullptr;
    this->stateStack.top()->Start();
    do {
        if(this->storedState != nullptr) {
            this->stateStack.top()->Pause();
            this->stateStack.push(std::unique_ptr<State>(this->storedState));
            this->stateStack.top()->Start();
            this->storedState = nullptr;
        }
        if(this->stateStack.top()->QuitRequested()) {
            this->stateStack.pop();
            Resources::Free();
            if(!this->stateStack.empty()) {
                this->stateStack.top()->Resume();
            }
        }
        else {
            this->CalculateDeltaTime();
            input.Update();
            this->stateStack.top()->Update(this->dt);
            this->stateStack.top()->Render();
            SDL_RenderPresent(this->renderer);
        }
    } while(!this->stateStack.empty() && !GameData::quitAll);
    
    while(!this->stateStack.empty()) {
        this->stateStack.pop();
    }
    Resources::Free();
}

void Game::CalculateDeltaTime() {
    int frame = SDL_GetTicks();
    this->dt = frame - this->frameStart;
    this->frameStart = frame;
}

int Game::GetDeltaTime() {
    return this->dt;
}

State& Game::GetCurrentState() {
    return *this->stateStack.top();
}

int Game::GetHeight() {
    return this->height;
}

int Game::GetWidth() {
    return this->width;
}

void Game::Push(State* state) {
    this->storedState = state;
}