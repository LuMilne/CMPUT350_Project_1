#include "GameEngine.h"
#include "GameContext.h"

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

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& name)
    : canvas(mWindow, mFont) {
    // Create game window
    mWindow =
        std::make_shared<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(width, height), 32), name);
    mWindow->setFramerateLimit(30);
    // Load resources. For P(1a), just the font from the header file
    /*if (!mFont->openFromMemory(&_font, _font_len)) {
        fprintf(stderr, "WARNING: Font did not load.\n");
    }*/
    // Set DrawContext using font
    canvas = DrawContext(mWindow, mFont);
    // Set GameContext using this and this.canvas
    context.mEngineView = this;
    context.ScreenContext = &canvas;
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

/**
 * @method Run
 * @arguments None
 * @description Gives control to the game engine. Will not return until the game window is closed or
 * all objects have been destroyed.
 */
void GameEngine::Run() {
    while (mWindow->isOpen())  // window is open
    {
//        std::cout << "Loop start\n";
//        std::cout << "0? ";
        // 0. Remove any objects that are now dead
        //std::cout << "active = " << activeObjects.size() << '\n'; 
        auto i = activeObjects.begin(); 
        while(  i != activeObjects.end() ) {
            if( !(*i)->IsAlive() ) {    // Dereferencing pointer to pointer. Blegh. Cleaner way to do this?
                activeObjects.erase(i);
                i = activeObjects.begin();  // Inefficient navigation of vector, but bug free. Maybe fix later.
            }
            else {i++;}
        }
//        std::cout << "0. ";

//        std::cout << "1? ";
        // 1. Activate and initialize any objects added during the last frame
        while( !incomingObjects.empty() ) {
            // Source: https://stackoverflow.com/questions/17436970/how-do-i-move-a-shared-ptr-object-between-containers-with-move-semantics
            // Time: 09/24/2026, 12:25pm
            // Referenced user quant's implementation of user David Schwartz' solution for passing shared_ptr between vectors
            incomingObjects.back()->Initialize(&context);
            activeObjects.push_back(std::move(incomingObjects.back()));
            assert(incomingObjects.back() == nullptr);
            incomingObjects.pop_back();
        }
//        std::cout << "1. ";

//        std::cout << "2? ";
        // 2. Process events
        //auto* temp = event->getIf<sf::Event::KeyPressed>();
        if (std::optional<sf::Event> event = mWindow->pollEvent())
        {
            if(event->is<sf::Event::Closed>()) {
                std::cout << "closing...\n";
                mWindow->close();
            }
            if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {    // Keypress controls for Player
                // Pass player input events to player
                char cmd = 'l';
                switch(keyPressed->code) {
                    case sf::Keyboard::Key::A:
                        cmd = 'a'; break;
                    case sf::Keyboard::Key::D:
                        cmd = 'd'; break;
                    case sf::Keyboard::Key::Space:
                        cmd = ' '; break;
                    case sf::Keyboard::Key::Escape:
                        mWindow->close(); break;
/*
                    case sf::Keyboard::Key::T:  // Test for collision and kill;
                        for(auto obj : activeObjects) {
                            if( auto sub = dynamic_cast<Enemy*>(obj.get()) ) {
                                auto b = sub->GetBounds();
                                auto e = Enemy({b.topLeft.x,b.topLeft.y});
                                sub->CollisionEnter(std::make_shared<CMPUT350::CollisionObject>(e));
                                break;
                            }
                        }
                        break;
*/
                    default:
                        break;
                };

                if( cmd != 'l' ) {
                    for( auto obj : activeObjects ) {
                        if( auto sub = dynamic_cast<Player*>(obj.get()) ) { // Get Player
                            if(sub != nullptr) {sub->HandleKeyEvent(&context,cmd);} // Pass key pressed to Player to handle response
                        }
                    }
                }
            }
            if(const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {  // Key release controls for Player
                // Pass player input events to player
                char cmd = 'l';
                switch(keyReleased->code) {
                    case sf::Keyboard::Key::A:
                        cmd = 'r'; break;
                    case sf::Keyboard::Key::D:
                        cmd = 'r'; break;
                    default:
                        break;
                };
                if( cmd != 'l' ) {
                    for( auto obj : activeObjects ) {
                        if( auto sub = dynamic_cast<Player*>(obj.get()) ) { // Get Player
                            if(sub != nullptr) {sub->HandleKeyEvent(&context,cmd);} // Pass key released to Player to handle response
                        }
                    }
                }
            }

        }
//        std::cout << "2. ";


        // 3. Update game objects
//        std::cout << "3? ";
        for( auto obj : activeObjects ) {
            obj->Update(&context);                  // TODO: Figure out GameContext
        }
//        std::cout << "3. ";

//        std::cout << "4?. ";
        // 4. Process collision events
        /* Example Code from Project1a doc
        std::shared_ptr<CollisionObject> objA = std::dynamic_pointer_cast<CollisionObject>(mGameObjects[a]);
        if (objA == nullptr)
            continue; // Not a collision object, skip
        */
        // Bullet collisions
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
//                    std::cout << "found " << found << "enemies\n";
                }
            }
        }
       
/*
        Collision Events:
            Bullet --> Enemy  (note: bullet object is source-independent. DON'T SHOOT YOURSELF)
            Bullet --> Player (later project phase?)
            Enemy --> Player (later project phase)
*/
//        std::cout << "4. ";


//        std::cout << "5? ";
        // 5. Late updates
        for( auto obj : activeObjects ) {
            obj->LateUpdate(&context);
        }
//        std::cout << "5. ";

        // Clear window
        mWindow->resetGLStates();

        // 6. Render background
//        std::cout << "6? ";
        for( auto obj : activeObjects ) {
            // Filter for GraphicsObject subclasses
            if( auto sub = dynamic_cast<CMPUT350::GraphicsObject*>(obj.get()) ) {
                sub->RenderBackground(&context);
            }
        }
//        std::cout << "6. ";

        // 7. Render foreground
//        std::cout << "7? ";
        for( auto obj : activeObjects ) {
            // Filter for GraphicsObject subclasses
            if( auto sub = dynamic_cast<CMPUT350::GraphicsObject*>(obj.get()) ) {
                sub->RenderForeground(&context);
            }
        }
//        std::cout << "7.\n";

        // Actually render to window
        mWindow->display();
        mWindow->clear();
//        std::cout << "Loop end\n";
    }
}

// Sample code for processing events

// bool GameEngine::ProcessEvents(GameContext *context)
//{
//	while (const std::optional event = mWindow->pollEvent())
//	{
//		if (event->is<sf::Event::Closed>())
//		{
//		}
//		else if (event->is<sf::Event::Resized>())
//		{
//		}
//		else if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>())
//		{
//			// use keyPressed->unicode to get character
//		}
//	}
// }

}  // namespace CMPUT350
