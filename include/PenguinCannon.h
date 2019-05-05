#ifndef PENGUICANNON
#define PENGUICANNON

#include <memory>
#include <string>
#include "GameObject.h"
#include "Component.h"

class PenguinCannon : public Component {
public:
    PenguinCannon(GameObject& associated);
    void Update(int dt);
    void Render();
    bool Is(const std::string& type);
    void Shoot();

private:
    float angle;
};

#endif