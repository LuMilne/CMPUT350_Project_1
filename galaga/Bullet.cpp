#include "Bullet.h"

CMPUT350::Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player, std::weak_ptr<CMPUT350::GameObject> parent)
{
    is_player = player;
    alive = true;
    loc = location;
    head = heading;
    velocity = head.y * 20;
    top_Point = loc;
    this->parent = parent;
}

bool CMPUT350::Bullet::IsPlayerBullet()
{
    if (auto p = parent.lock()) {
        return p->IsPlayer();
    }
    return false;
}


void CMPUT350::Bullet::Update(CMPUT350::GameContext* context)
{
    loc.y += velocity;
    top_Point.y = loc.y + 50;
    if (loc.y + 10 < 0) {
        Kill();
    }
    bounds = GetBounds();
}

void CMPUT350::Bullet::LateUpdate(CMPUT350::GameContext* context)
{
}
void CMPUT350::Bullet::ReceiveNotification(const std::string& key) {

}

void CMPUT350::Bullet::RenderForeground(CMPUT350::GameContext* context)
{
    context->ScreenContext->DrawLine(top_Point, loc, 5.f, colour);
}

void CMPUT350::Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    bounds = GetBounds();
    if (obj->GetBounds().IsInside(bounds.topLeft)) {
        Kill();
    }
}

void CMPUT350::Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj, const CMPUT350::Point2D &collisionPoint)
{

}

void CMPUT350::Bullet::Kill()
{
    alive = false;
}

bool CMPUT350::Bullet::IsAlive() const
{
    // TODO: Update code
    return alive;
}

const CMPUT350::Rect& CMPUT350::Bullet::GetBounds()
{
    // TODO: Update code
    bounds = Rect(loc.x, loc.y, 5, 10);
    return bounds;
}

CMPUT350::Point2D CMPUT350::Bullet::GetLocation() const {
    return loc;
}
float CMPUT350::Bullet::GetRotation() const {
    return std::numbers::pi/2;
}

