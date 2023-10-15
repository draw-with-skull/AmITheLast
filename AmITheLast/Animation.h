#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
class Animation
{
public:
	Animation(unsigned short FrameCount,unsigned int FrameWidth, unsigned int FrameHeight,unsigned int FrameRow,float FrameTime,bool IsContinuous, sf::Sprite* sprite);
	virtual ~Animation();
	void Update(const float& Dt,sf::Vector2f Direction);
	void Render( sf::RenderTarget* target);

private:
	sf::IntRect UVRect;
	sf::Sprite* Sprite;
	bool IsContinuous;
	bool IsActive;
	unsigned short FrameCount;
	unsigned short CurrentFrame;

	float FrameTime;
	float FrameTimeLeft; 
	

};
#endif

