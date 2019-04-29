#ifndef MINION
#define MINION

#include <memory>
#include <string>
#include <Vec2.h>
#include "GameObject.h"
#include "Component.h"

const float kRotationArc = 0.18;

class Minion : public Component{
public:
    Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
    void Update(int dt);
    void Render()       ;
    bool Is(const std::string &type);
    void Shoot(Vec2 target);
    void Start();

private:
    std::weak_ptr<GameObject> alienCenter;
    float arc;
};

#endif