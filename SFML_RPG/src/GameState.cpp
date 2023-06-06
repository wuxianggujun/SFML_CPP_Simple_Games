#include "include/GameState.h"

void GameState::initKeyBinds() {
    this->keyBinds.emplace("MOVE_LEFT", this->supportKeys->at("A"));
    this->keyBinds.emplace("MOVE_RIGHT", this->supportKeys->at("D"));
    this->keyBinds.emplace("MOVE_UP", this->supportKeys->at("W"));
    this->keyBinds.emplace("MOVE_DOWN", this->supportKeys->at("S"));
}

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int>* supportKeys) : State(window, supportKeys) {
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



