#include <cassert>
#include "Player.h"
#include "Bullet.h"

Player::Player(CMPUT350::Point2D loc)
{
    // TODO: Update code
    player_position = loc;
    alive = true;
}

void Player::Initialize(CMPUT350::GameContext* context)
{

}

void Player::Update(CMPUT350::GameContext* context)
{
    //the +40 is to account for the player size being 40 and player_position is the top left corner of its box
    if (player_position.x + velocity + 40 < context->ScreenContext->GetWindowWidth() && player_position.x + velocity > 0) {
        SetPosition(player_position, velocity);
    }else if (player_position.x + velocity + 40 >= context->ScreenContext->GetWindowWidth() || player_position.x + velocity <= 0) {
        SetPosition(player_position, 0);
    }

    SetPosition(player_position, velocity);

}

void Player::LateUpdate(CMPUT350::GameContext* context)
{
    std::cout << "(" << player_position.x << ',' << player_position.y << ")\n";
}

bool Player::HandleKeyEvent(CMPUT350::GameContext* context, char key)
{
    if (key == 'a') {
        velocity = -6;
        return true;
    }
    if (key == 'd') {
        velocity = 6;
        return true;
    }

    if (key == ' ') {
        if (bullet_one.expired()) {
            auto heading = CMPUT350::Point2D(0, -1);
            std::shared_ptr<CMPUT350::Bullet> new_bullet = std::make_shared<CMPUT350::Bullet>((player_position + 20.0f), heading, true);
            bullet_one = new_bullet;
            context->mEngineView->AddGameObject(new_bullet);
            shooting = true;
            return true;
        }

        if (bullet_two.expired()) {
            auto heading = CMPUT350::Point2D(0, -1);
            std::shared_ptr<CMPUT350::Bullet> new_bullet = std::make_shared<CMPUT350::Bullet>((player_position + 20.0f), heading, true);
            bullet_two = new_bullet;
            context->mEngineView->AddGameObject(new_bullet);
            shooting = true;
            return true;
        }
        return true;
    }
    if (key == 'r') {
        velocity = 0;
        return true;
    }

    velocity = 0;
    shooting = false;
    return false;
}

void Player::RenderBackground(CMPUT350::GameContext* context)
{
}

void Player::RenderForeground(CMPUT350::GameContext* context)
{
    bounds = GetBounds();
    context->ScreenContext->DrawRect(bounds, colour);
}

void Player::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    bounds = GetBounds();
    if (bounds.IsInside(obj->GetBounds().topLeft)) {
        Kill();
    }
}

void Player::Kill()
{
    alive = false;
}

bool Player::IsAlive() const
{
    return alive;
}

const CMPUT350::Rect& Player::GetBounds()
{
    bounds = CMPUT350::Rect(player_position.x, player_position.y, player_width, player_height);
    return bounds;
}

void Player::SetPosition(const CMPUT350::Point2D current_position, const float new_velocity) {
    player_position.x = current_position.x + new_velocity;

}
