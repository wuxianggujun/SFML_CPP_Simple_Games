#include "include/Game.h"
#include "include/GameState.h"

void Game::initWindow() {
    //创建SFML窗口
    std::ifstream ifstream("config/Window.ini");

    std::string tile = "None";
    sf::VideoMode window_bounds(1080, 720);
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;

    if (ifstream.is_open()) {
        std::getline(ifstream, tile);
        ifstream >> window_bounds.width >> window_bounds.height;
        ifstream >> framerate_limit;
        ifstream >> vertical_sync_enabled;
    }
    ifstream.close();

    this->window = new sf::RenderWindow(window_bounds, tile);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys() {
    this->supportedKeys = new std::map<std::string,int>();
    this->supportedKeys->emplace("Escape", sf::Keyboard::Key::Escape);
    this->supportedKeys->emplace("A", sf::Keyboard::Key::A);
    this->supportedKeys->emplace("D", sf::Keyboard::Key::D);
    this->supportedKeys->emplace("W", sf::Keyboard::Key::W);
    this->supportedKeys->emplace("S", sf::Keyboard::Key::S);
}

void Game::initStates() {
    states.push(new GameState(window, supportedKeys));
}


Game::Game() {
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game() {
    delete this->window;
    delete this->supportedKeys;
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
        //states.top()->render(window);
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






