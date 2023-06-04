#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
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

    //Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    sf::Font font;

    sf::Text text;


    //Game logic
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;

    //Game Objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initEnemies();

public:
    Game();
    virtual ~Game();

    const bool running() const;
    const bool getEndGame() const;

    void spawnEnemy();

    void pollEvents();
    void updateMousePositions();
    void updateText();
    void updateEnemies();
    void update();

    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();

};