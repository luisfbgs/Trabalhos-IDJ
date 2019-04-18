#ifndef CAMERAFOLLOWER
#define CAMERAFOLLOWER

#include <string>
#include "Component.h"
#include "GameObject.h"

class CameraFollower : public Component {
public:
    CameraFollower(GameObject& go);
    void Update(int dt);
    void Render();
    bool Is(const std::string& type);
};

#endif