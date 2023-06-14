//
// Created by WuXiangGuJun on 2023/6/12.
//
#include "include/MainMenuState.h"

void MainMenuState::initFonts() {
    if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
        throw ("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void MainMenuState::initButtons() {
    this->buttons["GAME_STATE"] = new Button(
            100, 100, 150, 50,
            &this->font, "New Game",
            sf::Color(70, 70, 70, 200),
            sf::Color(150, 150, 150, 255),
            sf::Color(20, 20, 20, 200));

    this->buttons["EXIT_STATE"] = new Button(
            100, 300, 150, 50,
            &this->font, "Quit",
            sf::Color(100, 100, 100, 200),
            sf::Color(150, 150, 150, 255),
            sf::Color(20, 20, 20, 200));

}


void MainMenuState::initKeyBinds() {

    std::ifstream ifs("config/MainMenuState_KeyBinds.ini");
    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keyBinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                             std::stack<State *> *states) : State(window,
                                                                  supportedKeys, states) {
    this->initFonts();
    this->initKeyBinds();
    this->initButtons();


    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Magenta);

}


MainMenuState::~MainMenuState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}

void MainMenuState::endState() {

    std::cout << "Ending MainMenuState!" << "\n";
}

void MainMenuState::updateInput(const float &deltaTime) {
    this->checkForQuit();


}

void MainMenuState::updateButtons() {
    /**
     * update all the buttons in the state and handles their functionality.
     */
    for (auto &it: this->buttons) {
        it.second->update(this->mousePosView);
    }
    //new game
    if (buttons["GAME_STATE"]->isPressed()) {
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }

    if (buttons["EXIT_STATE"]->isPressed()) {
        this->quit = true;
    }
}


void MainMenuState::update(const float &deltaTime) {
    this->updateMousePositions();
    this->updateInput(deltaTime);

    this->updateButtons();


}

void MainMenuState::renderButtons(sf::RenderTarget *target) {
    for (auto &it: this->buttons) {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;
    target->draw(background);
    this->renderButtons(target);
}






