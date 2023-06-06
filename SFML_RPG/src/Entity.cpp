//
// Created by WuXiangGuJun on 2023/6/6.
//

#include "include/Entity.h"

Entity::Entity() {
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
    this->shape.setFillColor(sf::Color::White);
    this->movementSpeed = 100.f;
}

Entity::~Entity() {

}

void Entity::move(const float &deltaTime, const float dir_x, const float dir_y) {
    shape.move(dir_x + movementSpeed * deltaTime, dir_y * movementSpeed * deltaTime);
}

void Entity::update(const float &deltaTime) {


}

void Entity::render(sf::RenderTarget *target) {
    target->draw(shape);
}

