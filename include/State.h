#ifndef STATE
#define STATE

#include <memory>
#include "GameObject.h"
#include "Sprite.h"
#include "Music.h"
#include "TileSet.h"

class State{
public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

private:
    void Input();
    void AddObject(int mouseX, int mouseY);
    std::vector<std::shared_ptr<GameObject>> objectArray;
    Music music;
    bool quitRequested;
    std::shared_ptr<TileSet> tileSet;
};

#endif