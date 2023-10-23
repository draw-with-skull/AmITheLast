#ifndef TESTSTATE_H
#define TESTSTATE_H
#include "State.h"
#include "Player.h"
#include"Room.h"
class TestState :public State
{
public:
    TestState(sf::RenderWindow* window, sf::View *view);
    virtual ~TestState();
    void Update(const float& dt);
    void Render(sf::RenderTarget *target);
    void UpdateKeyBinds(const float& dt);

private:
    Player Player;
    sf::View* View;
    Room* Level;
};
#endif

