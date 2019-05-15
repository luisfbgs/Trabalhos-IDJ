#ifndef STAGESTATE
#define STAGESTATE

#include <memory>
#include "GameObject.h"
#include "State.h"
#include "Sprite.h"
#include "Music.h"
#include "TileSet.h"

class StageState : public State{
public:
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
    
private:
    Music music;
    std::shared_ptr<TileSet> tileSet;
};

#endif