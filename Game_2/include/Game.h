#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "include/Player.h"
#include "include/SwagBall.h"


class Game {
private:
    sf::VideoMode videoMode;
    sf::RenderWindow *window;
    bool endGame;
    sf::Event sfmlEvent;

    Player player;

    int points;

    sf::Font font;
    sf::Text guiText;
    sf::Text endGameText;

    std::vector<SwagBall> swagBalls;
    float spawnTimerMax;
    float spawnTimer;
    int maxSwagBalls;

    void initVariables();

    void initWindow();

    void initFonts();

    void initText();

public:
    Game();

    ~Game();

    const bool &getEndGame() const;

    const bool running() const;

    void pollEvents();

    void spawnSwagBalls();

    const int randBallType() const;

    void updatePlayer();

    void updateCollision();

    void updateGui();

    void update();

    void renderGui(sf::RenderTarget *target);

    void render();

};