//
// Created by WuXiangGuJun on 2023/6/12.
//

#include "include/MainMenuState.h"

void MainMenuState::initKeyBinds() {

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

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys) : State(window,supportedKeys) {
    this->initKeyBinds();
    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Magenta);

}


MainMenuState::~MainMenuState() = default;

void MainMenuState::endState() {

    std::cout << "Ending GameState!" << "\n";
}

void MainMenuState::updateInput(const float &deltaTime) {
    this->checkForQuit();


}


void MainMenuState::update(const float &deltaTime) {
    this->updateInput(deltaTime);

}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;
    target->draw(background);
}



