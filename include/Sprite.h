#ifndef SPRITE
#define SPRITE

#include <string>
#include "Component.h"
#include "GameObject.h"

#define INCLUDE_SDL
#include "SDL_include.h"

class Sprite : public Component{
private:
    SDL_Texture* texture;  
    int width;
    int height;
    SDL_Rect clipRect;
    bool shouldMove;

public:
    Sprite(GameObject& associated, bool shouldMove = true);
    Sprite(GameObject& associated, const std::string &file, bool shouldMove = true);
    void Open(const std::string &file);  
    void SetClip(int x, int y, int w, int h);
    void Render(float x, float y);
    void Render();
    void Update(int dt);
    bool Is(std::string type);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
};

#endif