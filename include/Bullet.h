#ifndef BULLET
#define BULLET

#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
    void Update(int dt);
    void Render();
    bool Is(const std::string &type);
    int GetDamage();
    
private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};

#endif