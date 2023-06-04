#include "include/Game.h"

using namespace sf;

int main() {

    //Init srand
   std::srand( static_cast<unsigned>(time(nullptr)));

    //Init Game engine
    Game game;

    //Game Loop
    while (game.running()) {

        // Update
        game.update();

        //Render
        game.render();

    }

    return 0;
}
