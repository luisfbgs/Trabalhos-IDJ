#ifndef PENGUINBODY
#define PENGUINBODY

#include <memory>
#include <string>
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

class PenguinBody : public Component {
public:
    PenguinBody(GameObject& associated);
    ~PenguinBody();
    void Start();
    void Update(int dt);
    void Render();
    bool Is(const std::string& type);
    static PenguinBody* player;

private:
    std::weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;
};

#endif