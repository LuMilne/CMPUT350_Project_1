//
// Created by csobe on 2026-10-15.
//

#include "Enemies.h"

//
// Created by csobe on 2026-10-15.
//

/*
*Enemies are initialized with their initial location in the formation and a path that they will follow
*to reach that location. Once the enemy has moved into formation on the screen, it should wait for all
*enemies to come onto the screen before starting to attack the player as part of the main gameplay.
*The enemies should hover back and forth in formation; this can be synchronized using the current frame
*passed as part of the game context.

*The main difference between enemies is the behavior that they have when they attack and the amount
*of health that they have. An enemy with more than one health should change colors as it loses health.
*At least one enemy should initially have 1 health, and at least one enemy should initially have 2 health.
*The primary behavior difference expected is that different enemies will have different attack
*behaviors - they will follow different bezier curves when attacking.

*Enemies should move along their trajectories at a constant rate instead of speeding up and slowing
*down depending on the location of the control points in the bezier curve. Enemies should fire at
*the enemy as they attack, but the exact firing pattern is left to the student to decide. You can
*choose to imitate the original Galaga game closely, or design something significantly different.

*Enemies can only collide with the player and with player bullets. In either case they are destroyed.
*They should use the notification manager to inform the Galaga class that they have been destroyed.
*Different enemies should provide different points, and more points should be awarded for enemies
*that are not in formation versus in formation.

/*
 *_____________________________________________________________________________________
 *Enemy1
 *_____________________________________________________________________________________
 */
void Enemy1::Initialize(CMPUT350::GameContext *context) {
    health = 1;
}
void Enemy1::LateUpdate(CMPUT350::GameContext *context) {

}
bool Enemy1::Attack(CMPUT350::GameContext *context, const CMPUT350::Point2D &target) {

}
void Enemy1::RenderForeground(CMPUT350::GameContext *context) {

}

/*
 *_____________________________________________________________________________________
 *Enemy2
 *_____________________________________________________________________________________
 */
void Enemy2::Initialize(CMPUT350::GameContext *context){
    health = 2;
}
void Enemy2::LateUpdate(CMPUT350::GameContext *context) {

}
bool Enemy2::Attack(CMPUT350::GameContext *context, const CMPUT350::Point2D &target) {

}
void Enemy2::RenderForeground(CMPUT350::GameContext *context) {

}

/*
 *_____________________________________________________________________________________
 *Enemy3
 *_____________________________________________________________________________________
 */
void Enemy3::Initialize(CMPUT350::GameContext *context) {
    health = 2;
}
void Enemy3::LateUpdate(CMPUT350::GameContext *context) {

}
bool Enemy3::Attack(CMPUT350::GameContext *context, const CMPUT350::Point2D &target) {

}
void Enemy3::RenderForeground(CMPUT350::GameContext *context) {

}


