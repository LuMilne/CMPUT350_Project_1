#include "GameObject.h"

namespace CMPUT350 {

void GameObject::Initialize(GameContext *context) { return; }
void GameObject::Update(GameContext *context) { return; }
void GameObject::LateUpdate(GameContext *context) { return; }
void GameObject::RenderUI(GameContext *contextrender) { return; }
bool GameObject::HandleKeyEvent(GameContext *context, char key) { return false; }
bool GameObject::IsAlive() const { return this->alive; }
void GameObject::Kill() { this->alive = false; }

// Project 1b additions
void GameObject::ReceiveNotification(const std::string& key) { return; }
}  // namespace CMPUT350
