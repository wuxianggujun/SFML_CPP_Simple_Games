#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

/**
 * Class that acts as the game engines.
 * Wrapper class.
 */
class Game {

private:
    //Variables
    //Window
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    void initVariables();

    void initWindow();

public:
    Game();
    virtual ~Game();
    const bool running() const;
    void pollEvents();
    void update();
    void render();

};