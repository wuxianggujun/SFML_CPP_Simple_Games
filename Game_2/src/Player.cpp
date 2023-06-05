#include "include/Player.h"

void Player::initVariables() {
    movementSpeed = 5.f;
    hpMax = 10;
    hp = hpMax;
}

void Player::initShape() {
    shape.setFillColor(sf::Color::Green);
    shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y) {
    shape.setPosition(x, y);
    initVariables();
    initShape();
}

Player::~Player() {

}

const sf::RectangleShape &Player::getShape() const {
    return this->shape;
}

const int &Player::getHp() const {
    return this->hp;
}

const int &Player::getHpMax() const {
    return this->hpMax;
}

void Player::takeDamage(const int damage) {
    if (hp > 0)
        hp -= damage;
    if (hp < 0)
        hp = 0;
}

void Player::gainHealth(const int health) {
    if (hp < hpMax) {
        hp += health;
    }

    if (hp > hpMax)
        hp = hpMax;
}

void Player::updateInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        shape.move(-movementSpeed, 0.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        shape.move(movementSpeed, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        shape.move(0.f, -movementSpeed);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        shape.move(0.f, movementSpeed);
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget *target) {
    //Left
    if (shape.getGlobalBounds().left <= 0.f)
        shape.setPosition(0.f, shape.getGlobalBounds().top);

    //Right
    if (shape.getGlobalBounds().left + shape.getGlobalBounds().width >= target->getSize().x)
        shape.setPosition(target->getSize().x - shape.getGlobalBounds().width, shape.getGlobalBounds().top);

    //Top
    if (shape.getGlobalBounds().top <= 0.f)
        this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);

    //Bottom
    if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
        this->shape.setPosition(this->shape.getGlobalBounds().left,
                                target->getSize().y - this->shape.getGlobalBounds().height);

}

void Player::update(const sf::RenderTarget *target) {
    updateInput();
    updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget *target) {
    target->draw(shape);

}






