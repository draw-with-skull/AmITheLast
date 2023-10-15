#ifndef GAME_H
#define GAME_H
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<stack>
#include "State.h"
class Game
{
private:
	sf::RenderWindow *Window;
	sf::Event SfEvent;
	sf::Clock Clock;

	std::stack<State*> states;

	float Dt;
public:
	Game();
	virtual ~Game();

	void UpdateDeltaTime();
	void UpdateSFMLEvents();
	void Render();
	void Update();
	void Run();
private:
	void InitWindow();
	void InitStates();
	const sf::Vector2u WindowSize{ 1600u, 900u };
	const unsigned int PixelSize{ 3u };
};

#endif