#ifndef ENEMY_H
#define ENEMY_H

#include "../engine/CollisionObject.h"
#include "../engine/GameContext.h"

class Enemy : public CMPUT350::CollisionObject
{
public:
    Enemy(CMPUT350::Point2D loc);
    Enemy(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path) : enemy_position(loc), path(path) {}

    // GameObject Functions
    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    void LateUpdate(CMPUT350::GameContext* context) override;
    bool HandleKeyEvent(CMPUT350::GameContext* context, char key) override;
    void ReceiveNotification(const std::string& key) override;
    bool IsAlive() const override;
    void Kill() override;
    void SetPosition(const CMPUT350::Point2D& pos);

    //Gunna have multiple enemy types
    virtual bool Attack(CMPUT350::GameContext *context, const CMPUT350::Point2D &target) = 0;

    // Graphics Object Functions
    void RenderBackground(CMPUT350::GameContext* context) override;
    void RenderForeground(CMPUT350::GameContext* context) override;


    // Collision Object Functions
    void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) override;
    void CollisionEnter(const std::shared_ptr<CollisionObject> &obj, const CMPUT350::Point2D &collisionPoint) override;
    const CMPUT350::Rect& GetBounds() override;
    const CMPUT350::ShapeType GetType() override;

protected:
    enum class EnemyStatus {enter, in_formation, flying};
    EnemyStatus status;

    bool alive;
    float velocity;
    int health;
    bool odd_row = true;
    CMPUT350::Point2D enemy_position;
    CMPUT350::Point2D enemy_return_position;
    std::vector<CMPUT350::Point2D> path;
    std::string_view tag = "Enemy";
    float enemy_height = 30;
    float enemy_width = 35;
    CMPUT350::Rect bounds;
    CMPUT350::RGBColor colour = CMPUT350::Colors::red;
};


#endif

