#include <iostream>
#include "include/Game.h"

using namespace sf;

int main() {

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
