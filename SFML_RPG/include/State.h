#ifndef SFML_RPG_STATE_H
#define SFML_RPG_STATE_H

#include "include/Entity.h"

class State {
private:


protected:
    std::stack<State *> *states;
    sf::RenderWindow *window;
    std::map<std::string, int> *supportedKeys;
    std::map<std::string, int> keyBinds;
    bool quit;

    sf::Vector2i mousePoScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    std::vector<sf::Texture> textures;


    virtual void initKeyBinds() = 0;

public:

    State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);

    virtual ~State();

    const bool &getQuit() const;

    virtual void checkForQuit();

    virtual void endState() = 0;

    virtual void updateMousePositions();

    virtual void updateInput(const float &deltaTime) = 0;

    //纯虚函数
    virtual void update(const float &deltaTime) = 0;

    virtual void render(sf::RenderTarget *target = nullptr) = 0;

};


#endif //SFML_RPG_STATE_H
