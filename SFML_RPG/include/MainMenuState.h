#ifndef SFML_RPG_MAINMENUSTATE_H
#define SFML_RPG_MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State {

private:
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, Button *> buttons;

    void initFonts();

    void initKeyBinds() override;

    void initButtons();

public:
    MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*>* states);

    ~MainMenuState() override;


    void updateInput(const float &deltaTime) override;
    void updateButtons();
    void update(const float &deltaTime) override;

    void renderButtons(sf::RenderTarget *target = nullptr);
    void render(sf::RenderTarget *target) override;

    void endState() override;


};


#endif //SFML_RPG_MAINMENUSTATE_H
