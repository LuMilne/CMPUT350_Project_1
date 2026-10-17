#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "GameContext.h"
#include <string_view>

namespace CMPUT350 {
class Bullet;
class GameContext;

class GameObject {
private:
    bool alive = true;
public:
    virtual ~GameObject() = default;
    virtual void Initialize(GameContext *context);
    virtual void Update(GameContext *context);
    virtual void LateUpdate(GameContext *context);
    virtual void RenderUI(GameContext *context);
    virtual bool HandleKeyEvent(GameContext *context, char key);
    virtual bool IsAlive() const;
    virtual void Kill();
    // Project 1b additions
    virtual void ReceiveNotification(const std::string& key);

    virtual bool IsPlayer() const {return false;}
};
}  // namespace CMPUT350

#endif  // GAMEOBJECT_H
