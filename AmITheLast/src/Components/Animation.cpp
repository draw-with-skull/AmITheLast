#include "Animation.h"
#include<iostream>
Animation::Animation(unsigned short FrameCount, unsigned int FrameWidth, unsigned int FrameHeight, unsigned int FrameRow, float FrameTime, bool IsContinuous, sf::Sprite* sprite)
{
	this->FrameCount = FrameCount;
	this->FrameTime = FrameTime;
	this->FrameTimeLeft = FrameTime;
	this->IsContinuous = IsContinuous;

	this->UVRect.width = FrameWidth;
	this->UVRect.height = FrameHeight;
	this->UVRect.top = FrameRow * FrameHeight;

	this->IsActive = true;
	this->CurrentFrame = 0;
	this->Sprite = sprite;
	sprite->setOrigin(FrameWidth / 2.0, FrameHeight / 2.0);
}

Animation::~Animation()
{
}

void Animation::Update(const float& Dt, sf::Vector2f Direction)
{
	if (!this->IsActive)
		return;

	this->FrameTimeLeft -= Dt;

	if (this->FrameTimeLeft > 0) 
		return;

	this->FrameTimeLeft += this->FrameTime;
	this->CurrentFrame = ++this->CurrentFrame % this->FrameCount;
	this->UVRect.left = this->CurrentFrame * this->UVRect.width;
	if (Direction.x > 0) {
		this->Sprite->setScale(1, 1);
	}
	if(Direction.x < 0){
		this->Sprite->setScale(-1, 1);
	}
	
}

void Animation::Render( sf::RenderTarget* target)
{
	this->Sprite->setTextureRect(this->UVRect);
	target->draw(*this->Sprite);
}
