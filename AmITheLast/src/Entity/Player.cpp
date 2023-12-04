#include "Player.h"
#include <iostream>

Player::Player()
{
	this->Init();
	this->Animations = new AnimationManager(&this->Sprite,16,32);
	this->InitAnimations();
	this->CurrentState = AnimationState::IDLE;
}

Player::~Player()
{
	delete this->Animations;
}

void Player::Update(const float& dt)
{
	this->UpdateState();
	this->UpdatePosition(dt);
	this->Animations->Update(dt,this->CurrentState,this->Direction);
}

void Player::Render(sf::RenderTarget* target)
{
	this->Animations->Render(target);
}

void Player::SetPosition(sf::Vector2f position)
{
	this->Position = position;
}

sf::Vector2f Player::GetPosition()
{
	return this->Position;
}



void Player::UpdateState()
{
	this->Direction = { 0,0 };
	this->CurrentState = AnimationState::IDLE;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
	{
		this->Direction.x = -1;
		this->CurrentState = AnimationState::WALKING;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
	{ 
		this->Direction.y = 1; 
		this->CurrentState = AnimationState::WALKING;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
	{ 
		this->Direction.x = 1; 
		this->CurrentState = AnimationState::WALKING;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
	{ 
		this->Direction.y = -1; 
		this->CurrentState = AnimationState::WALKING;
	}
}


void Player::UpdatePosition(const float&dt)
{
	this->Position += this->Direction * dt * this->MovementSpeed;
	this->Sprite.setPosition(this->Position);
}

void Player::Init()
{
	this->MovementSpeed = 200;

	this->Texture = AssetImporter().ImportTexture("Lady_Dino", AssetType::CHARACTER);
	this->Sprite.setTexture(this->Texture);
	this->Sprite.setPosition(this->Position);
}

void Player::InitAnimations()
{
	this->Animations->AddAnimation(AnimationState::IDLE, 4, 0, 0.15, false);
	this->Animations->AddAnimation(AnimationState::WALKING, 5, 1, 0.10, false);
}