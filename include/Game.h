#ifndef GAME
#define GAME

#include <string>

#define INCLUDE_SDL
#include "SDL_include.h"

#include "State.h"

class Game {
public:
	~Game();
	static Game& GetInstance();
	int GetDeltaTime();
	void Run();
	int GetWidth();
	int GetHeight();
	SDL_Renderer* GetRenderer();
	State& GetState();

private:
	Game(const std::string &title, int width, int height);
	void CalculateDeltaTime();
	static Game* instance;
	int frameStart;
	int dt;
	int width;
	int height;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
};

#endif