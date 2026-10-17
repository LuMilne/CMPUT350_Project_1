//
// Created by csobe on 2026-10-16.
//

#include "Galaga.h"

#include "FontData.h"
namespace CMPUT350 {
class GameContext;

Galaga::Galaga(int width, int height) : canvas(mWindow, mFont){
    mWindow =
            std::make_shared<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(width, height), 32), name);
    mWindow->setFramerateLimit(30);
    // Load resources. For P(1a), just the font from the header file
    mFont = std::make_shared<sf::Font>();
    if (!mFont->openFromMemory(&_font, _font_len)) {
        fprintf(stderr, "WARNING: Font did not load.\n");
    }
}

Galaga::~Galaga() {
    mWindow->close();
}

void Galaga::Waiting() {
    if (coin) {
        state = GameState::startup;
        return;
    }

    while (std::optional<sf::Event> event = mWindow->pollEvent())
    {
        if(event->is<sf::Event::Closed>()) {
            mWindow->close();
            while(mWindow->pollEvent()) {} // Copied from GameEngine
            return;
        }

        if(const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {  // Key release controls for Player
            int code = (int)keyReleased->scancode;
            // Scancodes from google
            if(code == 6 || code == 76) {
                coin = true;
            }
        }

    }

}
void Galaga::StartUp() {

}
void Galaga::Waves() {

}
void Galaga::GamePlay() {

}
void Galaga::GameOver() {

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
