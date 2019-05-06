#ifndef COLLIDER
#define COLLIDER

#include <string>
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

class Collider : public Component {
public:
    Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
    void Update(int dt);
    void Render();
    bool Is(const std::string& type);
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
    Rect box;

private:
    Vec2 scale;
    Vec2 offset;
};

#endif