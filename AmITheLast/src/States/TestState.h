#ifndef TESTSTATE_H
#define TESTSTATE_H
#include "Components/State.h"
#include "Entity/Player.h"
#include "Components/TileMap.h"
#include <Components/MapGenerator.h>

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
    TileMap* Room;
    MapGenerator* MapG;
    sf::View* View; 
    sf::Texture RoomTexture;
    std::vector<sf::FloatRect>Collisions;
    
};
#endif

