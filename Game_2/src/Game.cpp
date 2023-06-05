#include "include/Game.h"

void Game::initVariables() {
    endGame = false;
    spawnTimerMax = 10.f;
    spawnTimer = spawnTimerMax;
    maxSwagBalls = 10;
    points = 0;
}

void Game::initWindow() {
    videoMode = sf::VideoMode(800, 600);
    window = new sf::RenderWindow(videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(60);
}

void Game::initFonts() {
    if (!font.loadFromFile("Fonts/PixellettersFull.ttf")) {
        std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
    }
}

void Game::initText() {
    //Gui text init
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(32);

    //End game text
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(60);
    this->endGameText.setPosition(sf::Vector2f(20, 100));
    this->endGameText.setString("YOU ARE DEAD, EXIT THE GAME!");
}

Game::Game() {
    initVariables();
    initWindow();
    initFonts();
    initText();
}

Game::~Game() {
    delete window;
}

const bool &Game::getEndGame() const {
    return endGame;
}

const bool Game::running() const {
    return window->isOpen();
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->sfmlEvent)) {
        switch (this->sfmlEvent.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
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

void Game::spawnSwagBalls() {
    if (spawnTimer < spawnTimerMax) {
        spawnTimer += 1.f;
    } else {
        if (swagBalls.size() < maxSwagBalls) {
            swagBalls.emplace_back(*window, randBallType());
            spawnTimer = 0.f;
        }
    }

}

const int Game::randBallType() const {
    int type = SwagBallTypes::DEFAULT;

    int randValue = rand() % 100 + 1;
    if (randValue > 60 && randValue <= 80)
        type = SwagBallTypes::DAMAGING;
    else if (randValue > 80 && randValue <= 100)
        type = SwagBallTypes::HEALING;

    return type;
}

void Game::updatePlayer() {
    this->player.update(this->window);

    if (this->player.getHp() <= 0)
        this->endGame = true;
}

void Game::updateCollision()
{
    //Check the collision
    for (size_t i = 0; i < this->swagBalls.size(); i++)
    {
        if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds()))
        {
            switch (this->swagBalls[i].getType())
            {
                case SwagBallTypes::DEFAULT:
                    this->points++;
                    break;
                case SwagBallTypes::DAMAGING:
                    this->player.takeDamage(1);
                    break;
                case SwagBallTypes::HEALING:
                    this->player.gainHealth(1);
                    break;
            }

            //Remove the ball
            this->swagBalls.erase(this->swagBalls.begin() + i);
        }
    }
}

void Game::updateGui()
{
    std::stringstream ss;

    ss << " - Points: " << this->points << "\n"
       << " - Health: " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";

    this->guiText.setString(ss.str());
}

void Game::update()
{
    this->pollEvents();

    if (!this->endGame)
    {
        this->spawnSwagBalls();
        this->updatePlayer();
        this->updateCollision();
        this->updateGui();
    }
}

void Game::renderGui(sf::RenderTarget* target)
{
    target->draw(this->guiText);
}

void Game::render()
{
    this->window->clear();

    //Render stuff
    this->player.render(this->window);

    for (auto i : this->swagBalls)
    {
        i.render(*this->window);
    }

    //Render gui
    this->renderGui(this->window);

    //Render end text
    if(this->endGame)
        this->window->draw(this->endGameText);

    this->window->display();
}