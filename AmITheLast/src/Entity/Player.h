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
	void SetHitBox(unsigned int width, unsigned int height,unsigned int offsetX,unsigned int offsetY);
	void SetLegHitBox(unsigned int width, unsigned int height, unsigned int offsetX, unsigned int offsetY);
	sf::Vector2f GetPosition();
	sf::FloatRect GetHitBox();
	sf::FloatRect GetLegHitBox();
private:
	void UpdateState();
	void UpdatePosition(const float&dt);
	void Init();
	void InitAnimations();
	AnimationManager *Animations;
	AnimationState CurrentState;
	sf::Vector2f Position, Direction;
	sf::FloatRect HitBox,LegHitBox;
};

