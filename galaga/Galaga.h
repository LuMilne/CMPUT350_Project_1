//
// Created by csobe on 2026-10-16.
//

#ifndef PROJECT1_GALAGA_H
#define PROJECT1_GALAGA_H
#include "GameContext.h"
namespace CMPUT350 {
class Galaga {

public:
    Galaga(int width, int height);
    ~Galaga();
    void Update(CMPUT350::GameContext* context);
    void Waiting();
    void StartUp();
    void Waves();
    void GamePlay();
    void GameOver();

private:
    enum class GameState {waiting, startup, waves, gameplay, gameover};
    GameState state = GameState::waiting;

    std::shared_ptr<sf::RenderWindow> mWindow;
    std::shared_ptr<sf::Font> mFont;
    DrawContext canvas;

    int start_frame = 0;
    int level = 1;
    int score = 0;
    int lives = 4;
    int wave = 0;
    int spawned_enemy_count = 0;
    int enemy_left_count = 0;
    bool coin = false;
    int next_attack_idx = 0;
};
}

#endif  // PROJECT1_GALAGA_H
