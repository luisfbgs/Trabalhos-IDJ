#ifndef ALIEN
#define ALIEN

#include <vector>
#include <queue>
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"

class Alien : public Component {
public:
    Alien(GameObject& associated, int nMinions);
    ~Alien();
    void Start();
    void Update(int dt);
    void Render();
    bool Is(std::string type);

private:
    class Action {
    public:
        struct ActionType{
            enum {MOVE, SHOOT};
        };
        Action (ActionType type, float x, float y);
        ActionType type;
        Vec2 pos;
    };
    Vec2 speed;
    int hp;
    std::queue<Action> taskQueue;
    std::vector< std::weak_ptr<GameObject> > minionArray;
};

#endif