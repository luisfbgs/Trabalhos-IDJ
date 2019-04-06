#ifndef COMPONENT
#define COMPONENT

#include <string>

class GameObject;

class Component{
public:
    Component(GameObject& associated);
    virtual ~Component();
    void virtual Update(float dt) = 0;
    void virtual Render() = 0;
    bool virtual Is(std::string type) = 0;
protected:
    GameObject& associated;
};

#endif