//
// Created by csobe on 2026-10-15.
//

#ifndef PROJECT1_ENEMIES_H
#define PROJECT1_ENEMIES_H
#pragma once
#include "Enemy.h"


class Enemy1 : public Enemy {
public:
    Enemy1(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D> &path)
    :Enemy(loc, path){}

    void Initialize(CMPUT350::GameContext *context) override;
    void LateUpdate(CMPUT350::GameContext *context) override;
    bool Attack(CMPUT350::GameContext *context, const CMPUT350::Point2D &target) override;
    void RenderForeground(CMPUT350::GameContext *context) override;


};

class Enemy2 : public Enemy {
public:
    Enemy2(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D> &path)
    :Enemy(loc, path){}

    void Initialize(CMPUT350::GameContext *context) override;
    void LateUpdate(CMPUT350::GameContext *context) override;
    bool Attack(CMPUT350::GameContext *context, const CMPUT350::Point2D &target) override;
    void RenderForeground(CMPUT350::GameContext *context) override;


};

class Enemy3 : public Enemy {
public:
    Enemy3(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D> &path)
    :Enemy(loc, path){}

    void Initialize(CMPUT350::GameContext *context) override;
    void LateUpdate(CMPUT350::GameContext *context) override;
    bool Attack(CMPUT350::GameContext *context, const CMPUT350::Point2D &target) override;
    void RenderForeground(CMPUT350::GameContext *context) override;


};

#endif  // PROJECT1_ENEMIES_H
