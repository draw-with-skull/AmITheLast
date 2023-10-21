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
	sf::RenderWindow* Window;
	sf::Event SfEvent;
	sf::Clock Clock;
	sf::View View;
	std::stack<State*> states;
	
	const unsigned int PixelSize{ 3u };
	float Dt;

};

#endif