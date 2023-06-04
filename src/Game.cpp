#include "include/Game.h"

void Game::initVariables() {
    this->window = nullptr;

    //Game logic
    this->endGame = false;
    this->points = 0;
    this->health = 20;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;

}

void Game::initWindow() {
    this->videoMode.height = 720;
    this->videoMode.width = 1080;

    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
    //设置窗口帧率限制
    this->window->setFramerateLimit(60);
}

void Game::initFonts() {
    if (this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
    }
}

void Game::initText() {
    this->text.setFont(this->font);
    this->text.setCharacterSize(24);
    this->text.setFillColor(sf::Color::White);
    this->text.setString("NONE");
}

void Game::initEnemies() {
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    /* this->enemy.setOutlineColor(sf::Color::Green);
     this->enemy.setOutlineThickness(1.f);*/
}


Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

Game::~Game() {
    delete this->window;
}

void Game::spawnEnemy() {
    /**
     * Spawns enemies and sets their color and positions.
     * Sets a random position.
     * Sets a random color.
     * Adds enemy to the vector.
     */
    this->enemy.setPosition(
            static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
            0.f);

    int type = rand() % 5;

    switch (type) {
        case 0:
            this->enemy.setSize(sf::Vector2f(10.f, 10.f));
            this->enemy.setFillColor(sf::Color::Magenta);
            break;
        case 1:
            this->enemy.setSize(sf::Vector2f(30.f, 30.f));
            this->enemy.setFillColor(sf::Color::Blue);
            break;
        case 2:
            this->enemy.setSize(sf::Vector2f(50.f, 50.f));
            this->enemy.setFillColor(sf::Color::Cyan);
            break;
        case 3:
            this->enemy.setSize(sf::Vector2f(70.f, 70.f));
            this->enemy.setFillColor(sf::Color::Red);
            break;
        case 4:
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            this->enemy.setFillColor(sf::Color::Green);
            break;
        default:
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            this->enemy.setFillColor(sf::Color::Yellow);
            break;
    }

    //Spawn the enemy
    this->enemies.push_back(this->enemy);

}


void Game::pollEvents() {
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::Resized:
                break;
            case sf::Event::LostFocus:
                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::TextEntered:
                break;
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                break;
            case sf::Event::KeyReleased:
                break;
            case sf::Event::MouseWheelMoved:
                break;
            case sf::Event::MouseWheelScrolled:
                break;
            case sf::Event::MouseButtonPressed:
                break;
            case sf::Event::MouseButtonReleased:
                break;
            case sf::Event::MouseMoved:
                break;
            case sf::Event::MouseEntered:
                break;
            case sf::Event::MouseLeft:
                break;
            case sf::Event::JoystickButtonPressed:
                break;
            case sf::Event::JoystickButtonReleased:
                break;
            case sf::Event::JoystickMoved:
                break;
            case sf::Event::JoystickConnected:
                break;
            case sf::Event::JoystickDisconnected:
                break;
            case sf::Event::TouchBegan:
                break;
            case sf::Event::TouchMoved:
                break;
            case sf::Event::TouchEnded:
                break;
            case sf::Event::SensorChanged:
                break;
            case sf::Event::Count:
                break;
        }

    }
}

void Game::updateMousePositions() {
    /**
     * Updates the mouse positions;
     * Mouse position relative to window (Vector2i)
     */
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText() {
    std::stringstream ss;
    ss << "Points: " << this->points << "\n"
       << "Health: " << this->health << "\n";

    this->text.setString(ss.str());
}


void Game::update() {
    this->pollEvents();

    if (!this->endGame) {
        this->updateMousePositions();
        this->updateEnemies();
        this->updateText();
    }

    if (this->health <= 0) {
        this->endGame = true;
    }
}

void Game::renderText(sf::RenderTarget &target) {
    target.draw(this->text);
}

void Game::renderEnemies(sf::RenderTarget &target) {
    for (auto &e: this->enemies) {
        target.draw(e);
    }
}

void Game::render() {
    /**
     * @return void
     * - clear old frame
     * - render objects
     * - display frame in window
     *
     */
    this->window->clear();

    //Draw game objects
    this->renderEnemies(*this->window);
    this->renderText(*this->window);

    this->window->display();
}

const bool Game::running() const {
    return this->window->isOpen();
}

const bool Game::getEndGame() const {
    return this->endGame;
}

void Game::updateEnemies() {
/**
 * Updates the enemy spawn timer and spawns enemies
 * when the total amount of enemies is smaller than the maximum.
 * Moves the enemies downwards.
 * Removes the enemies at the edge of the screen.
 */
    //Updating the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            //Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        } else
            this->enemySpawnTimer += 1.f;
    }

    for (int i = 0; i < this->enemies.size(); ++i) {

        this->enemies[i].move(0.f, 5.f);

        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "Health: " << this->health << "\n";
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!this->mouseHeld) {
            this->mouseHeld = true;
            bool deleted = false;

            for (size_t i = 0; i < this->enemies.size() && !deleted; i++) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    //Gain points
                    if (this->enemies[i].getFillColor() == sf::Color::Magenta)
                        this->points += 10;
                    else if (this->enemies[i].getFillColor() == sf::Color::Blue)
                        this->points += 7;
                    else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
                        this->points += 5;
                    else if (this->enemies[i].getFillColor() == sf::Color::Red)
                        this->points += 3;
                    else if (this->enemies[i].getFillColor() == sf::Color::Green)
                        this->points += 1;

                    std::cout << "Points: " << this->points << "\n";

                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }

            }
        }
    } else {
        this->mouseHeld = false;
    }

}




