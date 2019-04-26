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
    void Update(int dt);
    void Render();
    void Start();
    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
    
private:
    void AddObject(int mouseX, int mouseY);
    std::vector<std::shared_ptr<GameObject>> objectArray;
    Music music;
    bool quitRequested;
    std::shared_ptr<TileSet> tileSet;
    bool started;
};

#endif