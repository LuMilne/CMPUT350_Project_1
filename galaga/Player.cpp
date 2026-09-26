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
    }else if (player_position.x + velocity + 40 == context->ScreenContext->GetWindowWidth() || player_position.x + velocity == 0) {
        SetPosition(player_position, velocity);
        velocity = 0;
    }
}

void Player::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Player::HandleKeyEvent(CMPUT350::GameContext* context, char key)
{
    if (key == 'a') {
        velocity = -2;
        return true;
    }
    if (key == 'd') {
        velocity = 2;
        return true;
    }

    if (key == ' ') {
        shooting = true;
        return true;
    }

    shooting = false;
    return false;
}

void Player::RenderBackground(CMPUT350::GameContext* context)
{
}

void Player::RenderForeground(CMPUT350::GameContext* context)
{
}

void Player::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    CMPUT350::Rect bounds = GetBounds();
    bounds.IsInside(obj->GetBounds().topLeft);
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
    static CMPUT350::Rect sBounds(player_position.x, player_position.y, player_width, player_height);
    return sBounds;
}

void Player::SetPosition(const CMPUT350::Point2D current_position, const float new_velocity) {
    player_position.x = current_position.x + new_velocity;

}
