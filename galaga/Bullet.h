#ifndef BULLET_H
#define BULLET_H

#include "../engine/CollisionObject.h"
#include "../engine/GameContext.h"
namespace CMPUT350 {
    class Bullet : public CMPUT350::CollisionObject
    {
    public:
        Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player, std::weak_ptr<CMPUT350::GameObject> parent = {});
        bool IsPlayerBullet();

        // GameObject Functions
        //void Initialize(CMPUT350::GameContext* context) override;
        void Update(CMPUT350::GameContext* context) override;
        void LateUpdate(CMPUT350::GameContext* context) override;
        void ReceiveNotification(const std::string& key) override;
        bool IsAlive() const override;
        void Kill() override;

        // Graphics Object Functions
        void RenderForeground(CMPUT350::GameContext* context) override;
        Point2D GetLocation() const override;
        float GetRotation() const override;

        // Collision Object Functions
        void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) override;
        void CollisionEnter(const std::shared_ptr<CollisionObject> &obj, const CMPUT350::Point2D &collisionPoint) override;
        const Rect& GetBounds() override;
        const std::vector<CMPUT350::Shape> &GetShapes() override;
        const CMPUT350::ShapeType GetType() override;


    private:
        bool is_player;
        bool alive;
        Point2D loc;
        Point2D top_Point;
        Point2D head;
        Point2D biggest_y;
        Rect bounds;
        std::vector<CMPUT350::Shape> shapes;
        float velocity;
        RGBColor colour_player = Colors::green;
        RGBColor colour_enemy = Colors::red;
        std::weak_ptr<CMPUT350::GameObject> parent;
    };
}
#endif // BULLET_H
