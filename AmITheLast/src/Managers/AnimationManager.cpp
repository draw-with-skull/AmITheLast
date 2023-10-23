#include "AnimationManager.h"

AnimationManager::AnimationManager(sf::Sprite* SpriteSheet, unsigned int FrameWidth, unsigned int FrameHeight)
{
	this->SpriteSheet = SpriteSheet;
	this->FrameHeight = FrameHeight;
	this->FrameWidth = FrameWidth;
	this->CurrentKey = AnimationState::IDLE;
}

AnimationManager::~AnimationManager()
{
	for (auto& animation : this->Animations) {
		delete animation.second;
	}
	this->Animations.clear();
}

void AnimationManager::Update(const float& Dt, AnimationState Key,sf::Vector2f Direction)
{
	this->CurrentKey = Key;
	this->Animations[this->CurrentKey]->Update(Dt,Direction);
}

void AnimationManager::Render(sf::RenderTarget* Target)
{
	this->Animations[this->CurrentKey]->Render(Target);
}

void AnimationManager::AddAnimation(AnimationState Key, unsigned short FrameCount, unsigned short FrameRow, float FrameTime,bool IsContinuous)
{
	this->Animations.insert({Key,new Animation(FrameCount,this->FrameWidth,this->FrameHeight,FrameRow,FrameTime,IsContinuous,this->SpriteSheet)});
}

void AnimationManager::AddAnimation(AnimationState Key, unsigned short FrameCount, unsigned short FrameWidth, unsigned short FrameHeight, unsigned short FrameRow, float FrameTime, bool IsContinuous, sf::Sprite* SpriteSheet)
{
	this->Animations.insert({ Key,new Animation(FrameCount,FrameWidth,FrameHeight,FrameRow,FrameTime,IsContinuous,SpriteSheet) });
}

