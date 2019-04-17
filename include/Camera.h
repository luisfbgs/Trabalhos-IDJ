#ifndef CAMERA
#define CAMERA

#include "GameObject.h"
#include "Vec2.h"

class Camera {
public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(int dt);
    static Vec2 pos;
    static Vec2 speed;

private:
    static GameObject* focus;
};

#endif