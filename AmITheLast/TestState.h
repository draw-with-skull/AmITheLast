#ifndef TESTSTATE_H
#define TESTSTATE_H
#include "State.h"
#include "Player.h"
class TestState :public State
{
public:
    TestState(sf::RenderWindow* window);
    virtual ~TestState();
    void Update(const float& dt);
    void Render(sf::RenderTarget *target);
    void UpdateKeyBinds(const float& dt);

private:
    Player player;
};
#endif

