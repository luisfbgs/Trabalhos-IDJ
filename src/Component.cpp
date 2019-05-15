#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject& associated) : associated(associated) {}

Component::~Component() {}

void Component::NotifyCollision(GameObject& other) {
    (void)other;
}

void Component::Start() {}