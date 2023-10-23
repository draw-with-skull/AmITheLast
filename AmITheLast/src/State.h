#ifndef STATE_H
#define STATE_H

#include<vector>
#include<SFML/Graphics.hpp>
class State
{
public:
	State(sf::RenderWindow *window);
	virtual ~State();

	virtual void CheckForQuit(); 

	virtual void Render(sf::RenderTarget *taget=NULL) = 0;
	virtual void Update(const float &dt) = 0;
	virtual void UpdateKeyBinds(const float& dt) = 0;

	const bool& GetQuit()const;
protected:
	sf::RenderWindow* window;
	sf::View View;
	bool quit;
};
#endif
