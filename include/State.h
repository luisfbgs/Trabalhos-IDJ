#ifndef STATE
#define STATE

#include <memory>
#include <vector>
#include "GameObject.h"

class State {
public:
    State();
    virtual ~State();
    void virtual LoadAssets() = 0;
    void virtual Update(int dt) = 0;
    void virtual Render() = 0;
    void virtual Start() = 0;
    void virtual Pause() = 0;
    void virtual Resume() = 0;
    virtual std::weak_ptr<GameObject> AddObject(GameObject* object);
    virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* object);
    bool PopRequested();
    bool QuitRequested();
    
protected:
    void StartArray();
    virtual void UpdateArray(int dt);
    virtual void RenderArray();
    bool popRequested;
    bool quitRequested;
    bool started;
    std::vector<std::shared_ptr<GameObject>> objectArray;
};

#endif