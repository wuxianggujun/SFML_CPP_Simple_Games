#include "include/Game.h"

void Game::initVariables() {
    this->window = nullptr;
    this->fullScreen = false;
    this->deltaTime = 0.f;

}

void Game::initWindow() {
    //创建SFML窗口
    std::ifstream ifstream("config/Window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();


    std::string tile = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    //无符号抗锯齿级别
    unsigned antialiasing_level = 0;

    if (ifstream.is_open()) {
        std::getline(ifstream, tile);
        ifstream >> window_bounds.width >> window_bounds.height;
        ifstream >> fullScreen;
        ifstream >> framerate_limit;
        ifstream >> vertical_sync_enabled;
        ifstream >> antialiasing_level;
    }
    ifstream.close();
    this->windowSettings.antialiasingLevel = antialiasing_level;
    if (this->fullScreen)
        this->window = new sf::RenderWindow(window_bounds, tile,
                                            sf::Style::Fullscreen,
                                            windowSettings);
    else
        this->window = new sf::RenderWindow(window_bounds, tile, sf::Style::Titlebar | sf::Style::Close,
                                            windowSettings);

    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys() {

    std::ifstream ifs("config/Supported_Keys.ini");
    if (ifs.is_open()) {
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value) {
            this->supportedKeys[key] = key_value;
        }
    }
    ifs.close();

    //DEBUG REMOVE LATER!
    for (auto i: this->supportedKeys) {
        std::cout << i.first << " " << i.second << "\n";
    }

}

void Game::initStates() {
    states.push(new MainMenuState(window, &supportedKeys, &this->states));
}


Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game() {
    delete this->window;
    //删除所有state
    while (!states.empty()) {
        delete states.top();
        states.pop();
    }
}

void Game::endApplication() {
    std::cout << "Ending Application!" << "\n";

}

void Game::updateDeltaTime() {
    /**
     * Updates the at variable with the time it takes to update and render one frame.
     */
    this->deltaTime = this->deltaTimeClock.restart().asSeconds();

}

void Game::updateSFMLEvents() {
    while (this->window->pollEvent(this->sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) {
            window->close();
        }
    }
}

void Game::update() {
    this->updateSFMLEvents();
    if (!states.empty() && window->isOpen()) {
        states.top()->update(this->deltaTime);
        if (states.top()->getQuit()) {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
        //Application end
    else {
        endApplication();
        this->window->close();
    }


}

void Game::render() {
    window->clear();
    //Render Items
    if (!states.empty()) {
        states.top()->render();
    }

    window->display();

}

void Game::run() {

    while (this->window->isOpen()) {
        this->updateDeltaTime();
        this->update();
        this->render();
    }

}







