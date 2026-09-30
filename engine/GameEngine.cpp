#include "GameEngine.h"
#include "GameContext.h"

/// @brief
namespace CMPUT350 {
#include "FontData.h"
#include "Player.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cassert>

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& name) {
    // Create game window
    mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(sf::Vector2u(width, height), 32), name);
    mWindow->setFramerateLimit(30);
    // Load resources. For P(1a), just the font from the header file
    if (!mFont->openFromMemory(&_font, _font_len)) {
    	fprintf(stderr, "WARNING: Font did not load.\n");
    }
    // Set DrawContext using font
    canvas = DrawContext(mWindow, mFont);
    // Set GameContext using this and this.canvas
    context.mEngineView = this;
    context.ScreenContext = canvas;
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
    while (true)  // window is open
    {
        // 0. Remove any objects that are now dead
        for( auto i = activeObjects.begin(); i != activeObjects.end(); /*No default iteration*/) {
            if( !(*i)->IsAlive() ) {    // Dereferencing pointer to pointer. Blegh. Cleaner way to do this?
                activeObjects.erase(i);
            }
            else i++;
        }

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

        // 2. Process events
        if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>())
        {
             // Pass player input events to player
            if (keyPressed->unicode == 'a' || keyPressed->unicode == 'd' || keyPressed->unicode == ' ') {
                // Get player
                std::shared_ptr<GameObject> player;
                for( auto obj : activeObjects ) {
                    if( typeid(obj.get()) == typeid(Player) ) {
                        player = obj;
                        break;
                    }
                }
                // Check for player collection
                if (player.get() == nullptr) { 
                    fprintf(stderr, "WARNING: Player was not found.\n");
                }
                else {
                    player->HandleKeyEvent(context, keyPressed->unicode);
                }
            }
        }


        // 3. Update game objects
        for( auto obj : activeObjects ) {
            obj->Update(&context);                  // TODO: Figure out GameContext
        }

        // 4. Process collision events
        /* Example Code from Project1a doc
        std::shared_ptr<CollisionObject> objA = std::dynamic_pointer_cast<CollisionObject>(mGameObjects[a]);
        if (objA == nullptr)
            continue; // Not a collision object, skip
        */
        /*
        Collision Events:
            Bullet --> Enemy  (note: bullet object is source-independent. DON'T SHOOT YOURSELF)
            Bullet --> Player (later project phase?)
            Enemy --> Player (later project phase)
        */

        // 5. Late updates
        for( auto obj : activeObjects ) {
            // Filter for GraphicsObject subclasses
            obj->LateUpdate(context);
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
        mWindow->draw(&context);
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
