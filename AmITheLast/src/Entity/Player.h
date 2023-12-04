#pragma once
#include "Components/Entity.h"
#include "Managers/AnimationManager.h"

class Player : Entity
{
public:
	Player();
	virtual ~Player();
	// Inherited via Entity
	virtual void Update(const float& dt) override;
	virtual void Render(sf::RenderTarget* target) override;
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();
private:
	void UpdateState();
	void UpdatePosition(const float&dt);
	void Init();
	void InitAnimations();
	AnimationManager *Animations;
	AnimationState CurrentState;
	sf::Vector2f Position;
	sf::Vector2f Direction;
};

