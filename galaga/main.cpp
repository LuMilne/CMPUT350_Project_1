#include <random>

#include "Enemy.h"
#include "Galaga.h"
#include "GameEngine.h"
#include "Player.h"
#include "Stars.h"

int main()
{
    //     CMPUT350::GameEngine engine(768, 1024, "Engine");
    //     //auto player = std::make_shared<Player>(CMPUT350::Point2D(768 / 2, 900));
    //     //engine.AddGameObject(player);
    //     engine.AddGameObject(std::make_shared<Stars>(250, CMPUT350::Rect(0, 0, 768, 1024)));
    //     for (int row = 0; row < 5; row++)
    //     {
    //         for(int col = 0; col < 8; col++) {
    //             auto enemy = std::make_shared<Enemy>(CMPUT350::Point2D((40+653/7*col), (100*row+1)+50));
    //             engine.AddGameObject(enemy);
    //         }
    //     }
    //     engine.Run();
    // }
    // return 0;
    CMPUT350::GameEngine engine(768, 1024, "Galaga");
    auto game = std::make_shared<CMPUT350::Galaga>(768, 1024);
    engine.AddGameObject(game);
    engine.Run();

    return 0;

}
