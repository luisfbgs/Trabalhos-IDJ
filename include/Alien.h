#ifndef ALIEN
#define ALIEN

#include <vector>
#include <queue>
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"

const int kAlienCooldown = 500;

class Alien : public Component {
public:
    Alien(GameObject& associated, int nMinions);
    ~Alien();
    void Start();
    void Update(int dt);
    void Render();
    bool Is(const std::string &type);
    void NotifyCollision(GameObject& other);
    void Shoot(Vec2 target);
    static int alienCount;

private:
    Vec2 speed;
    int hp;
    int nMinions;
    std::vector<std::weak_ptr<GameObject>> minionArray;
    enum AlienState { MOVING, RESTING };
    AlienState state;
    Timer restTimer;
    Vec2 destination;
};

#endif