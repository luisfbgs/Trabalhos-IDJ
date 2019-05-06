#ifndef COMPONENT
#define COMPONENT

#include <string>

class GameObject;

class Component{
public:
    Component(GameObject& associated);
    virtual ~Component();
    void virtual Update(int dt) = 0;
    void virtual Render() = 0;
    bool virtual Is(const std::string& type) = 0;
    void virtual NotifyCollision(GameObject& other);
    void virtual Start();
protected:
    GameObject& associated;
};

#endif