#include "GameEngine.h"
#include "GameContext.h"
#include "MathUtil.h"

/// @brief
#include "FontData.h"
#include "../galaga/Player.h"
#include "../galaga/Bullet.h"
#include "../galaga/Enemy.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cassert>
#include "GraphicsObject.h"
namespace CMPUT350 {

    // Initialize Engine
GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& name)
    : canvas(mWindow, mFont) {
    // Create game window
    mWindow =
        std::make_shared<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(width, height), 32), name);
    mWindow->setFramerateLimit(30);
    // Load resources. For P(1a), just the font from the header file
    mFont = std::make_shared<sf::Font>();
    if (!mFont->openFromMemory(&_font, _font_len)) {
        fprintf(stderr, "WARNING: Font did not load.\n");
    }
    // Set GameContext using this and this.canvas
    context.mEngineView = this;
    context.ScreenContext = &canvas;

    // Project 1b additions, lemilne 10-16-2026

    // Default keybindings
    keyPressEvents = {
        {(int) sf::Keyboard::Scan::Num1,    "start"},
        {(int) sf::Keyboard::Scan::Num5,    "coin"},
        {(int) sf::Keyboard::Scan::Left,    "left"},
        {(int) sf::Keyboard::Scan::A,       "left"},
        {(int) sf::Keyboard::Scan::Right,   "right"},
        {(int) sf::Keyboard::Scan::D,       "right"},
        {(int) sf::Keyboard::Scan::Space,   "shoot"}
    };
    keyReleaseEvents = {
        {(int) sf::Keyboard::Scan::Left,    "stop"},
        {(int) sf::Keyboard::Scan::A,       "stop"},
        {(int) sf::Keyboard::Scan::Right,   "stop"},
        {(int) sf::Keyboard::Scan::D,       "stop"},
    };
}

GameEngine::~GameEngine() {
    // Cleanup resources
    activeObjects.clear();
    incomingObjects.clear();
    mWindow->close();
}

void GameEngine::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    incomingObjects.push_back(gameObject);
}

//
// Project 1b function additions
// created by lemilne 10-16-2026
//

// Associate keypress scancode with event for NotificationManager
void GameEngine::InstallKeyDownNotification(int scanCode,  const std::string &notification) {
    keyPressEvents[scanCode] = notification;    // SFML keyboard scancodes are enums and can be passed as integers
}
// Associate keyrelease scancode with event for NotificationManager
void GameEngine::InstallKeyUpNotification(int scanCode,  const std::string &notification) {
    keyReleaseEvents[scanCode] = notification;
}

// Getters for iterators over incomingObjects
GameEngine::const_iterator GameEngine::cbegin() const { return this->incomingObjects.begin(); }
GameEngine::const_iterator GameEngine::cend() const { return this->incomingObjects.end(); }
// Getters for iterators over activeObjects
GameEngine::const_iterator GameEngine::begin() const { return this->activeObjects.begin(); }
GameEngine::const_iterator GameEngine::end() const { return this->activeObjects.end(); }

/**
 * @method Run
 * @arguments None
 * @description Gives control to the game engine. Will not return until the game window is closed or
 * all objects have been destroyed.
 */
void GameEngine::Run() {
    while (mWindow->isOpen())  // window is open
    {
        // 0. Remove any objects that are now dead
        auto i = begin(); 
        while(  i != end() ) {
            if( !(*i)->IsAlive() ) {    // Dereferencing pointer to pointer. Blegh. Cleaner way to do this?
                activeObjects.erase(i);
                i = begin();  // Inefficient navigation of vector, but bug free. Maybe fix later.
            }
            else {i++;}
        }
        // 1. Activate and initialize any objects added during the last frame
        while( cbegin() != cend() ) {
            // Source: https://stackoverflow.com/questions/17436970/how-do-i-move-a-shared-ptr-object-between-containers-with-move-semantics
            // Time: 09/24/2026, 12:25pm
            // Referenced user quant's implementation of user David Schwartz' solution for passing shared_ptr between vectors
            context.CurrObject = incomingObjects.back();    // Set initializing object as context.CurrObject for the duration
            incomingObjects.back()->Initialize(&context);
            activeObjects.push_back(std::move(incomingObjects.back()));
            assert(incomingObjects.back() == nullptr);
            incomingObjects.pop_back();
            context.CurrObject.reset();
        }

        // 2. Process events

        // AI Usage: Microsoft Copilot
        // Date: 09/30/2026, 7:50pm
        // Prompt: "why does program stop responding after closing window with mouse"
        // Implementation: converted step-2 base if-loop to while-loop to clear queued events and prevent slowdown. Also added a while loop to clear residual events after close event is triggered.
        while (std::optional<sf::Event> event = mWindow->pollEvent())
        {
            if(event->is<sf::Event::Closed>()) {
                mWindow->close();
                while(mWindow->pollEvent()) {} // Implemented from AI request documented above
                return;
            }
            if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {    // Keypress controls for Player
                int code = (int)keyPressed->scancode;
                // Check GameEngine map for keypress events associated with the scancode and pass to NotificationManager
                if(keyPressEvents.contains(code)) {
                    context.mNotificationManager->Notify(keyPressEvents.at(code));
                }
            }

            if(const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {  // Key release controls for Player
                int code = (int)keyReleased->scancode;
                // Check GameEngine map for keypress events associated with the scancode and pass to NotificationManager
                if(keyReleaseEvents.contains(code)) {
                    context.mNotificationManager->Notify(keyReleaseEvents.at(code));
                }
            }

        }

        // 3. Update game objects
        for( auto obj : activeObjects ) {
            obj->Update(&context);
        }
        // 4. Process collision events
        for( auto obj = begin(); obj != end(); obj++ ) {
            // Filter for collision objects
            if( auto col1 = std::dynamic_pointer_cast<CollisionObject>(*obj) ) {
                // When found, iterate over remaining objects in search of possible collisions
                for( auto it = std::next(obj); it != end(); it++ ) {
                    if( auto col2 = std::dynamic_pointer_cast<CollisionObject>(*it) ) {
                        // Get bounding boxes
                        if(col1->GetType() == CMPUT350::ShapeType::kLine) {
                            if(col2->GetType() == CMPUT350::ShapeType::kLine) {
                                // No line/line collisions
                            }
                            else {
                                if( col2->GetBounds().IsInside(col1->GetLocation()) ) { // Line/Rect Collision
                                    col2->CollisionEnter(col1, col1->GetLocation());    
                                    col1->CollisionEnter(col2);
                                }
                            }
                        }
                        else {
                            if(col2->GetType() == CMPUT350::ShapeType::kLine) {
                                if( col1->GetBounds().IsInside(col2->GetLocation()) ) { // Rect/Line Collision
                                    col1->CollisionEnter(col2, col2->GetLocation());    
                                    col2->CollisionEnter(col1);
                                }
                            }
                            else {
                                if( col1->GetBounds().IsInside(col2->GetBounds()) ) {   // Rect/Rect Collision
                                    col1->CollisionEnter(col2);                         
                                    col2->CollisionEnter(col1);
                                }
                            }
                        }
                    }
                }
            }
        }
    /*  OLD CODE
        for( auto obj : activeObjects ) {
            // Filter for Bullet subclasses
            if(auto bul = dynamic_cast<Bullet*>(obj.get()) ) {
                // For each bullet, check if it is Player bullet
                if(bul->IsPlayerBullet()) {
                    // Check for collision with each enemy
                    int found = 0;
                    for( auto chk : activeObjects ) {
                        auto enm = dynamic_cast<Enemy*>(chk.get());
                        if(enm != nullptr && chk->IsAlive()) {
                            found++;
                            enm->CollisionEnter(std::dynamic_pointer_cast<CMPUT350::CollisionObject>(obj));
                            if(!enm->IsAlive()) {   // If collision is detected, kill both and escape search instance
                                bul->Kill();
                            }
                        }
                    }
                }
            }
        }
    */
        // 5. Late updates
        for( auto obj : activeObjects ) {
            obj->LateUpdate(&context);
        }

        // Clear window
        mWindow->resetGLStates();

        // 6. Render background
        for( auto obj : activeObjects ) {
            // Filter for GraphicsObject subclasses
            if( auto sub = dynamic_cast<CMPUT350::GraphicsObject*>(obj.get()) ) {
                sub->RenderBackground(&context);
            }
        }

        // 7. Render foreground
        for( auto obj : activeObjects ) {
            // Filter for GraphicsObject subclasses
            if( auto sub = dynamic_cast<CMPUT350::GraphicsObject*>(obj.get()) ) {
                sub->RenderForeground(&context);
            }
        }

        // Actually render to window
        mWindow->display();
        mWindow->clear();
    }
}
}  // namespace CMPUT350
