#ifndef PLAYER_H
#define PLAYER_H

#include "CollisionObject.h"

class Player : public CMPUT350::CollisionObject
{
public:
    Player(CMPUT350::Point2D loc);

    // GameObject Functions
    void Initialize(CMPUT350::GameContext* context) override;
    void SetPosition(CMPUT350::Point2D point2_d, float velocity);
    void Update(CMPUT350::GameContext* context) override;
    void LateUpdate(CMPUT350::GameContext* context) override;
    bool HandleKeyEvent(CMPUT350::GameContext* context, char key) override;
    bool IsAlive() const override;
    void Kill() override;

    // Graphics Object Functions
    void RenderBackground(CMPUT350::GameContext* context) override;
    void RenderForeground(CMPUT350::GameContext* context) override;


    // Collision Object Functions
    void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) override;
    const CMPUT350::Rect& GetBounds() override;

private:
    //Negative left, Positive Right
    float velocity = 0;
    bool alive;
    CMPUT350::Point2D player_position;
    std::string_view tag = "Player";
    int shoot_cooldown = 6;
    bool shooting = false;
    float player_height = 40;
    float player_width = 40;
};

#endif
