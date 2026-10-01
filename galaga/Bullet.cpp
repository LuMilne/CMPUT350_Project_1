#include "Bullet.h"

CMPUT350::Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player)
{
    is_player = player;
    alive = true;
    loc = location;
    head = heading;
    velocity = head.y * 20;
    top_Point = loc;
}

bool CMPUT350::Bullet::IsPlayerBullet()
{
    return is_player;
}

void CMPUT350::Bullet::Initialize(CMPUT350::GameContext* context)
{
//    std::cout << "Bullet spawned at (" << loc.x << ',' << loc.y << ")\n";
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

bool CMPUT350::Bullet::HandleKeyEvent(CMPUT350::GameContext* context, char key)
{
    return false;
}

void CMPUT350::Bullet::RenderBackground(CMPUT350::GameContext* context)
{
}

void CMPUT350::Bullet::RenderForeground(CMPUT350::GameContext* context)
{
    context->ScreenContext->DrawLine(top_Point, loc, 5.f, colour);
}

void CMPUT350::Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    std::cout << "bullet: checking collision...\n";
    bounds = GetBounds();
    if (obj->GetBounds().IsInside(bounds.topLeft)) {
        Kill();
    }
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
