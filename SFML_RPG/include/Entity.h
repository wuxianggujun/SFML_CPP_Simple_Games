//
// Created by WuXiangGuJun on 2023/6/6.
//

#ifndef SFML_RPG_ENTITY_H
#define SFML_RPG_ENTITY_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Entity {
private:


protected:
    sf::RectangleShape shape;
    float movementSpeed;


public:
    Entity();

    virtual ~Entity();

    virtual void move(const float &deltaTime, const float dir_x, const float dir_y);

    virtual void update(const float &deltaTime);

    virtual void render(sf::RenderTarget* target);

};


#endif //SFML_RPG_ENTITY_H
