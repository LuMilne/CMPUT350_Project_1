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
    }else if (player_position.x + velocity + 80 >= context->ScreenContext->GetWindowWidth() || player_position.x + velocity <= 0) {
        SetPosition(player_position, 0);
    }

}

void Player::LateUpdate(CMPUT350::GameContext* context)
{
//    std::cout << "(" << player_position.x << ',' << player_position.y << ")\n";
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
    //bounds = GetBounds();
    CMPUT350::Rect player_obj(player_position.x, player_position.y, player_width, player_height);
    //context->ScreenContext->DrawRect(player_obj, colour);

    CMPUT350::Point2D pixel(player_position.x, player_position.y);
    context->ScreenContext->DrawRect(ShipPart(pixel, 5, 0, 1, 3), colour);
    context->ScreenContext->DrawRect(ShipPart(pixel, 2, 3, 1, 2), colour);
    context->ScreenContext->DrawRect(ShipPart(pixel, 8, 3, 1, 2), colour);
    context->ScreenContext->DrawRect(ShipPart(pixel, 4, 3, 3, 2), colour);
    context->ScreenContext->DrawRect(ShipPart(pixel, 0, 6, 1, 2), colour);
    context->ScreenContext->DrawRect(ShipPart(pixel, 2, 5, 7, 3), colour);
    context->ScreenContext->DrawRect(ShipPart(pixel, 10, 6, 1, 2), colour);
    context->ScreenContext->DrawRect(ShipPart(pixel, 0, 8, 11, 2), colour);
    context->ScreenContext->DrawRect(ShipPart(pixel, 2, 10, 6, 1), colour);


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

CMPUT350::Rect& Player::ShipPart(CMPUT350::Point2D p, float px, float py, float w, float h) {
    float pixel_x = 4 * px;
    float pixel_y = 4 * py;
    CMPUT350::Point2D pixel(p.x + pixel_x, p.y + pixel_y);

    float height = 4 * h;
    float width = 4 * w;

    CMPUT350::Rect part(pixel, width, height);
    return part;

}
