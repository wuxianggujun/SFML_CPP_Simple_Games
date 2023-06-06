#include "include/State.h"

State::State(sf::RenderWindow *window, std::map<std::string, int> *supportKeys) {
    this->window = window;
    this->supportKeys = supportKeys;
    this->quit = false;
}


State::~State() {

}

void State::checkForQuit() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        quit = true;
    }

}

const bool &State::getQuit() const {
    return quit;
}

