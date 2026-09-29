#include "Bullet.h"

Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player)
{
    is_player = player;
    alive = true;
    loc = location;
    head = heading;
    velocity = head.y * 20;
}

bool Bullet::IsPlayerBullet()
{
    return is_player;
}

void Bullet::Initialize(CMPUT350::GameContext* context)
{
}

void Bullet::Update(CMPUT350::GameContext* context)
{
    loc += velocity;
}

void Bullet::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Bullet::HandleKeyEvent(CMPUT350::GameContext* context, char key)
{
    return false;
}

void Bullet::RenderBackground(CMPUT350::GameContext* context)
{
}

void Bullet::RenderForeground(CMPUT350::GameContext* context)
{
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    bounds = GetBounds();
    if (bounds.IsInside(obj->GetBounds().topLeft)) {
        Kill();
    }
}

void Bullet::Kill()
{
}

bool Bullet::IsAlive() const
{
    // TODO: Update code
    return alive;
}

const CMPUT350::Rect& Bullet::GetBounds()
{
    // TODO: Update code
    static CMPUT350::Rect sBounds(loc.x, loc.y, 5, 10);
    return sBounds;
}
