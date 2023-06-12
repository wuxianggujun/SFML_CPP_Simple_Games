#include "include/GameState.h"

void GameState::initKeyBinds() {

    std::ifstream ifs("config/GameState_KeyBinds.ini");
    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keyBinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys) : State(window,
                                                                                                  supportedKeys) {
    this->initKeyBinds();
}

GameState::~GameState() = default;

void GameState::updateInput(const float &deltaTime) {
    this->checkForQuit();

    //Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_LEFT"))))
        player.move(deltaTime, -1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_RIGHT"))))
        player.move(deltaTime, 1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_UP"))))
        player.move(deltaTime, 0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_DOWN"))))
        player.move(deltaTime, 0.f, 1.f);

}


void GameState::update(const float &deltaTime) {
    this->updateMousePositions();
    this->updateInput(deltaTime);

    player.update(deltaTime);
}

void GameState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;
    player.render(target);
}

void GameState::endState() {

    std::cout << "Ending GameState!" << "\n";
}



