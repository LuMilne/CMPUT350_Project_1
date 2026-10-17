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
    if (loc.y + 10 < 0 || loc.y > 1024) {
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
    if (is_player) {
        context->ScreenContext->DrawLine(top_Point, loc, 5.f, colour_player);
    }else {
        context->ScreenContext->DrawLine(top_Point, loc, 5.f, colour_enemy);
    }
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
    if (!alive) {
        if (collisionPoint.y > top_Point.y) {
            top_Point.y = collisionPoint.y;
            return;
        }
    }

    top_Point = collisionPoint;
    Kill();
}

void CMPUT350::Bullet::Kill()
{
    //Call a renderForeground after kill is called
    alive = false;
}

bool CMPUT350::Bullet::IsAlive() const
{
    return alive;
}

const CMPUT350::Rect& CMPUT350::Bullet::GetBounds()
{
    bounds = Rect(loc.x, loc.y, 5, 10);
    return bounds;
}

CMPUT350::Point2D CMPUT350::Bullet::GetLocation() const {
    return loc;
}
float CMPUT350::Bullet::GetRotation() const {
    return std::numbers::pi/2;
}

