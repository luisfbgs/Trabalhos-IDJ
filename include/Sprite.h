#ifndef SPRITE
#define SPRITE

#include <string>
#include <memory>
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"

#define INCLUDE_SDL
#include "SDL_include.h"

class Sprite : public Component{
public:
    Sprite(GameObject& associated, const std::string &file, int frameCount = 1, int frameTime = 1, int msToSelfDestruct = 0);
    void SetScale(float scaleX, float scaleY); 
    Vec2 GetScale();
    void SetAngle(float angle);
    float GetAngle();
    void Open(const std::string &file);  
    void SetClip(int x, int y, int w, int h);
    void Render(float x, float y);
    void Render();
    void Update(int dt);
    bool Is(const std::string &type);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(int frameTime);

private:
    std::shared_ptr<SDL_Texture> texture;  
    int width;
    int height;
    SDL_Rect clipRect;
    Vec2 scale;
    float angle;
    int frameCount;
    int currentFrame;
    int timeElapsed;
    int frameTime;
    int msToSelfDestruct;
    Timer selfDestructCount;
};

#endif