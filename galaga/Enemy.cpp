#include "Enemy.h"
#include "Bullet.h"

Enemy::Enemy(CMPUT350::Point2D loc)
{
    // TODO: Update code
    enemy_position = loc;
    alive = true;
}

void Enemy::Initialize(CMPUT350::GameContext* context)
{
}

void Enemy::Update(CMPUT350::GameContext* context)
{
    bounds = GetBounds();
}

void Enemy::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Enemy::HandleKeyEvent(CMPUT350::GameContext* context, char key)
{
    return false;
}

void Enemy::RenderBackground(CMPUT350::GameContext* context)
{
}

void Enemy::RenderForeground(CMPUT350::GameContext* context)
{
    context->ScreenContext->DrawRect(bounds, colour);
}

void Enemy::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    bounds = GetBounds();
    if (bounds.IsInside(obj->GetBounds().topLeft)) {
        Kill();
    }
    if (obj->GetBounds().IsInside(bounds.topLeft)) {
        Kill();
    }
}

void Enemy::Kill()
{
    alive = false;
}

bool Enemy::IsAlive() const
{
    // TODO: Update code
    return alive;
}

const CMPUT350::Rect& Enemy::GetBounds()
{
    // TODO: Update code
    bounds = CMPUT350::Rect(enemy_position.x, enemy_position.y, enemy_width, enemy_height);
    return bounds;
}
