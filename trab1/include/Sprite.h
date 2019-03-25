#ifndef SPRITE
#define SPRITE

#include <string>

#define INCLUDE_SDL
#include "SDL_include.h"

class Sprite{
private:
    SDL_Texture* texture;  
    int width;
    int height;
    SDL_Rect clipRect;

public:
    Sprite();
    Sprite(const std::string &file);
    ~Sprite();
    void Open(const std::string &file);  
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
};

#endif