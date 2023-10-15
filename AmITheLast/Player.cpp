#include "Player.h"
#include <iostream>

Player::Player()
{
	this->Init();
	this->animation = new Animation(9,16,32,0,0.15,false,&this->Sprite);
}

Player::~Player()
{
	delete this->animation;
}

void Player::Update(const float& dt)
{
	this->UpdateDirection();
	this->UpdatePosition(dt);
	this->animation->Update(dt,this->Direction);
}

void Player::Render(sf::RenderTarget* target)
{
	this->animation->Render(target);
}

void Player::Init()
{
	this->MovementSpeed = 200;
	this->Position.x = 300;
	this->Position.y = 300;

	this->Texture = AssetImporter().ImportTexture("Lady_Dino", AssetImporter::AssetType::CHARACTER);
	this->Sprite.setTexture(this->Texture);
	this->Sprite.setPosition(this->Position);
}


void Player::UpdateDirection()
{
	this->Direction = { 0,0 };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { this->Direction.x = -1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { this->Direction.y = 1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { this->Direction.x = 1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { this->Direction.y = -1; }
}

void Player::UpdatePosition(const float&dt)
{
	this->Position += this->Direction * dt * this->MovementSpeed;
	this->Sprite.setPosition(this->Position);
}
