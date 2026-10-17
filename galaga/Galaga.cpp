//
// Created by csobe on 2026-10-16.
//

#include "Galaga.h"
namespace CMPUT350 {
class GameContext;

void Waiting() {

}
void StartUp() {

}
void Waves() {

}
void GamePlay() {

}
void GameOver() {

}

void Galaga::Update(CMPUT350::GameContext* context) {
    switch (state) {
        case GameState::waiting:
            Waiting();
            break;
        case GameState::startup:
            StartUp();
            break;
        case GameState::waves:
            Waves();
            break;
        case GameState::gameplay:
            GamePlay();
            break;
        case GameState::gameover:
            GameOver();
            break;
    }


}



}
