#include "Enemy.h"
#include "Bullet.h"
#include "Bezier.h"

Enemy::Enemy(CMPUT350::Point2D loc)
{
    // TODO: Update code
    enemy_position = loc;
}

void Enemy::Initialize(CMPUT350::GameContext* context)
{
    status = EnemyStatus::enter;
    alive = true;
}

void Enemy::Update(CMPUT350::GameContext* context)
{

    switch (status) {
        case EnemyStatus::enter: {
            //float seg = (path.size() - 1) / 3;
            int FPA = 180;

            float animation_time = (context->currentFrame % FPA) / static_cast<float>(FPA);
            CMPUT350::Point2D square_position = CMPUT350::Bezier::GetPoint(path, animation_time);
            SetPosition({square_position.x, square_position.y});

            if (animation_time >= 1) {
                status = EnemyStatus::in_formation;
            }
            break;
        }
        case EnemyStatus::in_formation: {
            if (odd_row) {
                velocity = 2;
            }else {
                velocity = -2;
            }

            enemy_position.x += velocity;

            if (enemy_position.x + 20 >= 720) {
                odd_row = false;
                enemy_position.y += 80;

            }else if (enemy_position.x - 20 <= 0) {
                odd_row = true;
                enemy_position.y += 80;
            }

            enemy_return_position = enemy_position;
            break;
        }
        case EnemyStatus::flying: {
            break;
        }
    }

    bounds = GetBounds();
}

void Enemy::LateUpdate(CMPUT350::GameContext* context)
{
}

void Enemy::ReceiveNotification(const std::string& key) {
    if (key == "left") {
        velocity = -2;
        return;
    }

    if (key == "right") {
        velocity = 2;
        return;
    }

    if (key == "enemy_shoot") {
        //Attack();
    }
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

const CMPUT350::ShapeType Enemy::GetType() { return CMPUT350::ShapeType::kRect; }

const std::vector<CMPUT350::Shape>& Enemy::GetShapes() {
    shapes.clear();
    shapes.emplace_back(GetBounds());
    return shapes;
}

void Enemy::SetPosition(const CMPUT350::Point2D& pos) {
    enemy_position = pos;
}

void Enemy::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj,
                           const CMPUT350::Point2D& collisionPoint) {
    CollisionEnter(obj);
}

CMPUT350::Point2D Enemy::GetLocation() const {
    return CMPUT350::Point2D(
        enemy_position.x + enemy_width / 2.0f,
        enemy_position.y + enemy_height / 2.0f);
}

float Enemy::GetRotation() const {
    return 0.0f;
}