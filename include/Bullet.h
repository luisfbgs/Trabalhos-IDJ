#ifndef BULLET
#define BULLET

#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frames, bool targetsPlayer = true);
    void Update(int dt);
    void Render();
    bool Is(const std::string &type);
    int GetDamage();
    void NotifyCollision(GameObject& other);
    bool targetsPlayer;
    
private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};

#endif