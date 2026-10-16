
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

namespace CMPUT350 {
class GameEngine;
}

#include "EngineView.h"
#include "GameObject.h"
#include "MathUtil.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <memory>
#include <unordered_map>

namespace CMPUT350 {

class DrawContext;

class GameEngine : public EngineView {
public:
    GameEngine(unsigned int width, unsigned int height, const std::string& name);
    ~GameEngine();

    GameEngine(const GameEngine&) = delete;             // Prevent copy-construction
    GameEngine(GameEngine&&) = delete;                  // Prevent move-construction
    GameEngine& operator=(const GameEngine&) = delete;  // Prevent assignment
    GameEngine& operator=(GameEngine&&) = delete;       // Prevent move-assignment

    void AddGameObject(std::shared_ptr<GameObject> gameObject) override;
    // int: scancode for keypress                                   (i.e. left arrowkey scancode = 75)
    // string &notification: message sent to NotificationManager    (i.e. "MoveLeft")
	virtual void InstallKeyDownNotification(int, const std::string &notification) override;
	virtual void InstallKeyUpNotification(int, const std::string &notification) override;

    void Run();

private:
    std::shared_ptr<sf::RenderWindow> mWindow;
    std::shared_ptr<sf::Font> mFont;
    DrawContext canvas;
    GameContext context;
    std::vector<std::shared_ptr<GameObject>> activeObjects;
    std::vector<std::shared_ptr<GameObject>> incomingObjects;
    // Project 1b element additions
    std::unordered_map<int, std::string> keyPressEvents;
    std::unordered_map<int, std::string> keyReleaseEvents;
};

}  // namespace CMPUT350

#endif  // GAMEENGINE_H
