#ifndef FACE
#define FACE

#include <string>
#include "Component.h"
#include "GameObject.h"

class Face : public Component {
public:
    Face(GameObject& associated);
    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
private:
    int hitpoints;
};

#endif