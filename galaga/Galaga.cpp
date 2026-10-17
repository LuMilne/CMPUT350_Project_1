//
// Created by csobe on 2026-10-16.
//

#include "Galaga.h"

#include "Enemies.h"
#include "FontData.h"
#include "Player.h"
#include "Stars.h"
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

void Initialize(GameContext *context) {
    // Register as listener for notifications. context.CurrObject should be this object during init
    context->mNotificationManager->Register(context->CurrObject, "coin");
    context->mNotificationManager->Register(context->CurrObject, "start");
}

void Galaga::Waiting(CMPUT350::GameContext* context) {
    //Makes stars for background, checks to make sure its only done once
    if (!stars_made) {
        context->mEngineView->AddGameObject(std::make_shared<Stars>(250, CMPUT350::Rect(0, 0, 768, 1024)));
        stars_made = true;
    }

    //Checks if both a coin is inserted and game is started
    if (coin) {
        if (started) {
            state = GameState::startup;
            return;
        }
    }

    // while (std::optional<sf::Event> event = mWindow->pollEvent())
    // {
    //     if(event->is<sf::Event::Closed>()) {
    //         mWindow->close();
    //         while(mWindow->pollEvent()) {} // Copied from GameEngine
    //         return;
    //     }
    //
    //     if(const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {  // Key release controls for Player
    //         int code = (int)keyReleased->scancode;
    //         // Scancodes from google
    //         if(code == 6 || code == 76) {
    //             coin = true;
    //         }else if (code == 1 || code == 79) {
    //             started = true;
    //         }
    //     }
    //
    // }


    sf::Text text(*mFont);
    if (!coin) {
        text.setString("Press 5 To Insert Coin");
    }else {
        text.setString("Press 1 To Start Game");
    }
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Yellow);
    text.setStyle(sf::Text::Bold);
    text.setPosition({window_width / 2 , window_height / 2});

    mWindow->draw(text);
}
void Galaga::StartUp(CMPUT350::GameContext* context) {
    //Displays text to see score
    // sf::Text score_text(*mFont);
    // std::string score_string= "Score: " + std::to_string(score);
    // score_text.setString(score_string);
    // score_text.setCharacterSize(50);
    // score_text.setFillColor(sf::Color::White);
    // score_text.setStyle(sf::Text::Bold);
    // score_text.setPosition({30 , 20});
    // mWindow->draw(score_text);
    DisplayScoreText();

    //Displays text to see level
    // sf::Text level_text(*mFont);
    // std::string level_string = "Level: " + std::to_string(level);
    // level_text.setString(level_string);
    // level_text.setCharacterSize(50);
    // level_text.setFillColor(sf::Color::White);
    // level_text.setStyle(sf::Text::Bold);
    // level_text.setPosition({window_width - 30 , 20});
    // mWindow->draw(level_text);
    DisplayLevelText();

    auto player = std::make_shared<Player>(CMPUT350::Point2D(768 / 2, 900));
    context->mEngineView->AddGameObject(player);
    state = GameState::waves;
}
void Galaga::Waves(CMPUT350::GameContext* context) {
    //Lets us call a new wave when our enemies move down the screen
    int new_wave = 292;
    int enemy_wave_type = 1;

    DisplayScoreText();
    DisplayLevelText();

    if (context->currentFrame % new_wave == 0) {
        switch (enemy_wave_type) {
            //Spawns all 3 enemy types in a rotating order
            case 1:
                for (int i = 0; i < 8; i++) {
                    CMPUT350::Point2D form_spot(20 + i * 70, 340);
                    auto enemy = std::make_shared<Enemy1>(form_spot, MakePath(form_spot));
                    context->mEngineView->AddGameObject(enemy);
                }
                ++enemy_wave_type;
                spawned_enemy_count + 8;
                break;
            case 2:
                for (int i = 0; i < 8; i++) {
                    CMPUT350::Point2D form_spot(20 + i * 70, 340);
                    auto enemy = std::make_shared<Enemy2>(form_spot, MakePath(form_spot));
                    context->mEngineView->AddGameObject(enemy);
                }
                ++enemy_wave_type;
                spawned_enemy_count + 8;
                break;
            case 3:
                for (int i = 0; i < 8; i++) {
                    CMPUT350::Point2D form_spot(20 + i * 70, 340);
                    auto enemy = std::make_shared<Enemy3>(form_spot, MakePath(form_spot));
                    context->mEngineView->AddGameObject(enemy);
                }
                enemy_wave_type = 1;
                spawned_enemy_count + 8;
                break;
        }
    }

    if (spawned_enemy_count == 40) {
        state = GameState::gameplay;
    }
}
void Galaga::GamePlay(CMPUT350::GameContext* context) {
    DisplayScoreText();
    DisplayLevelText();

    //NOTE: make sure if player loses a life, enemies finish attack animation before respawn. Pause enemy side to side movement
}
void Galaga::GameOver(CMPUT350::GameContext* context) {

}

void Galaga::Update(CMPUT350::GameContext* context) {
    //Switch cases for game state
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

std::vector<CMPUT350::Point2D> Galaga::MakePath(const CMPUT350::Point2D &form_spot) {

    //AI usage:
    //Claude AI
    //Date: 2026/10/16 10:01 pm
    //Prompt: My window dimensions are 768, 1024. What might a cubic bezier curves points look like from middle left to top left of screen
    //Implementation: Helped get initial bezier curve points and a rough range. Obviously sent to top left so adjustments to get into right position needed
    //Helpfulness: allowed me to make a basic starter bezier curve without heavy trial and error to find initial values.
    std::vector<CMPUT350::Point2D> path({
        {-60, 500},
        {250, 512},
        {350, 450},
        {450, 600},
        {500, 450},
        {form_spot.x - 100, form_spot.y + 150},
        {form_spot.x, form_spot.y}
    });

    return path;

}

void Galaga::ReceiveNotification(const std::string& key) {
    if (key == "coin") {
        coin = true;
    }else if (key == "start" && coin) { //Checks to see if we hit "1" to start and we hit "5" for coin
        started = true;
    }
}

//Displays text to see level
void Galaga::DisplayScoreText() {
    sf::Text score_text(*mFont);
    std::string score_string= "Score: " + std::to_string(score);
    score_text.setString(score_string);
    score_text.setCharacterSize(50);
    score_text.setFillColor(sf::Color::White);
    score_text.setStyle(sf::Text::Bold);
    score_text.setPosition({30 , 20});
    mWindow->draw(score_text);
}

//Displays text to see level
void Galaga::DisplayLevelText() {
    sf::Text level_text(*mFont);
    std::string level_string = "Level: " + std::to_string(level);
    level_text.setString(level_string);
    level_text.setCharacterSize(50);
    level_text.setFillColor(sf::Color::White);
    level_text.setStyle(sf::Text::Bold);
    level_text.setPosition({window_width - 30 , 20});

    mWindow->draw(level_text);
}


}
