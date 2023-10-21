#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H
#include<map>
#include"Animation.h"
enum class AnimationState
	{
		IDLE,
		WALKING
	};
class AnimationManager
{
public:
	AnimationManager(sf::Sprite* SpriteSheet,unsigned int FrameWidth, unsigned int FrameHeight);
	virtual ~AnimationManager();

	void Update(const float& Dt, AnimationState Key,sf::Vector2f Direction);
	void Render(sf::RenderTarget* Target);
	void AddAnimation(AnimationState Key, unsigned short FrameCount, unsigned short FrameRow, float FrameTime, bool IsContinuous);
	void AddAnimation(AnimationState Key,unsigned short FrameCount,unsigned short FrameWidth,unsigned short FrameHeight,unsigned short FrameRow,float FrameTime, bool IsContinuous,sf::Sprite *SpriteSheet);

private:
	std::map<AnimationState, Animation*> Animations;
	sf::Sprite *SpriteSheet;
	AnimationState CurrentKey;
	unsigned short FrameWidth;
	unsigned short FrameHeight;
};
#endif

