#ifndef SFML_RPG_GAME_H
#define SFML_RPG_GAME_H

#include "MainMenuState.h"

class Game {
private:

    sf::RenderWindow *window;
    sf::Event sfEvent;


    sf::Clock deltaTimeClock;
    float deltaTime;

    std::stack<State *> states;
    std::map<std::string, int> supportedKeys;

    void initWindow();

    void initKeys();

    void initStates();


public:
    Game();

    virtual ~Game();

    //Regular
    void endApplication();

    //Update
    void updateDeltaTime();

    void updateSFMLEvents();

    void update();

    //Render
    void render();

    //Core
    void run();

};

#endif //SFML_RPG_GAME_H
