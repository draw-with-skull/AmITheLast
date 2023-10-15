#pragma once
#include "Entity.h"
#include "Animation.h"

class Player : Entity
{
public:
	Player();
	virtual ~Player();
	// Inherited via Entity
	virtual void Update(const float& dt) override;
	virtual void Render(sf::RenderTarget* target) override;
private:
	void Init();
	void UpdateDirection();
	void UpdatePosition(const float&dt);
	Animation *animation;
	sf::Vector2f Position;
	sf::Vector2f Direction;
};

