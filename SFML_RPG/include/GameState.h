#ifndef SFML_RPG_GAMESTATE_H
#define SFML_RPG_GAMESTATE_H

#include "State.h"

class GameState : public State {
private:
    Entity player;

    void initKeyBinds() override;

public:
    GameState(sf::RenderWindow *window, std::map<std::string, int>* supportKeys);

    ~GameState() override;

    void updateInput(const float &deltaTime) override;

    void update(const float &deltaTime) override;

    void render(sf::RenderTarget *target) override;

    void endState() override;


};


#endif //SFML_RPG_GAMESTATE_H
