#include "include/State.h"

State::State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys) {
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->quit = false;
}


State::~State() {


}

void State::checkForQuit() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE")))) {
        quit = true;
    }

}

const bool &State::getQuit() const {
    return quit;
}

void State::updateMousePositions() {
    this->mousePoScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    //将窗口的像素映射为坐标
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));


}

