#ifndef SFML_RPG_MAINMENUSTATE_H
#define SFML_RPG_MAINMENUSTATE_H

#include "GameState.h"

class MainMenuState :public State{

private:
    sf::RectangleShape background;


    void initKeyBinds() override;

public:
    MainMenuState(sf::RenderWindow *window, std::map<std::string, int>* supportedKeys);
    ~MainMenuState() override;


    void updateInput(const float &deltaTime) override;

    void update(const float &deltaTime) override;

    void render(sf::RenderTarget *target) override;

    void endState() override;




};


#endif //SFML_RPG_MAINMENUSTATE_H
