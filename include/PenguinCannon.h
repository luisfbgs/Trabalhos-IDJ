#ifndef PENGUICANNON
#define PENGUICANNON

#include <memory>
#include <string>
#include "GameObject.h"
#include "Timer.h"
#include "Component.h"

const int kShootCooldown = 200;

class PenguinCannon : public Component {
public:
    PenguinCannon(GameObject& associated);
    void Update(int dt);
    void Render();
    bool Is(const std::string& type);
    void Shoot();

private:
    float angle;
    Timer shootCooldown;
};

#endif