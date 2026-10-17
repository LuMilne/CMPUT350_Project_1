//
// Created by csobe on 2026-10-16.
//

#include "Galaga.h"

#include "FontData.h"
namespace CMPUT350 {
class GameContext;

Galaga::Galaga(int width, int height) : canvas(mWindow, mFont){

    window_width = width;
    window_height = height;
    mWindow =
            std::make_shared<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(width, height), 32), "Galaga");
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

void Galaga::Waiting(CMPUT350::GameContext* context) {
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

    if (!coin) {
        sf::Text text(*mFont);
        text.setString("Press 5 To Insert Coin");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Yellow);
        text.setStyle(sf::Text::Bold);
        text.setPosition({window_width / 2 , window_height / 2});
    }

}
void Galaga::StartUp(CMPUT350::GameContext* context) {
    //Draw lvl number top left, score top right, and draw ship
}
void Galaga::Waves(CMPUT350::GameContext* context) {

}
void Galaga::GamePlay(CMPUT350::GameContext* context) {

}
void Galaga::GameOver(CMPUT350::GameContext* context) {

}

void Galaga::Update(CMPUT350::GameContext* context) {
    switch (state) {
        case GameState::waiting:
            Waiting(context);
            break;
        case GameState::startup:
            StartUp(context);
            break;
        case GameState::waves:
            Waves(context);
            break;
        case GameState::gameplay:
            GamePlay(context);
            break;
        case GameState::gameover:
            GameOver(context);
            break;
    }


}



}
