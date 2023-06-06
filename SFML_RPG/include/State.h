#ifndef SFML_RPG_STATE_H
#define SFML_RPG_STATE_H

#include "include/Entity.h"

class State {

private:

protected:
    sf::RenderWindow *window;
    std::map<std::string, int> *supportKeys;
    std::map<std::string,int> keyBinds;
    bool quit;
    //Resources
    std::vector<sf::Texture> textures;

   virtual void initKeyBinds() = 0;

public:
    State(sf::RenderWindow *window, std::map<std::string, int> *supportKeys);

    State();

    virtual ~State();

    const bool &getQuit() const;

    virtual void checkForQuit();

    virtual void endState() = 0;

    virtual void updateInput(const float &deltaTime) = 0;

    //纯虚函数
    virtual void update(const float &deltaTime) = 0;

    virtual void render(sf::RenderTarget *target = nullptr) = 0;

};


#endif //SFML_RPG_STATE_H
