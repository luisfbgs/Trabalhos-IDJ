#include <string>
#include "CameraFollower.h"
#include "GameObject.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go) {}

void CameraFollower::Update(int dt) {
    (void)dt;
    this->associated.box.lefUp = Camera::pos;
}

void CameraFollower::Render() {}

bool CameraFollower::Is(const std::string& type) {
    return type == "CameraFollower";
}