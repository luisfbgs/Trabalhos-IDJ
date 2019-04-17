#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <vector>
#include <memory>
#include <string>
#include "Rect.h"
#include "Component.h"

class GameObject {
public:
    GameObject();
    ~GameObject();
    void Update(int dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(std::shared_ptr<Component> cpt);
    void RemoveComponent(std::shared_ptr<Component> cpt);
    std::shared_ptr<Component> GetComponent(std::string type);
    Rect box;

private:
    std::vector<std::shared_ptr<Component>> components;
    bool isDead;
};

#endif