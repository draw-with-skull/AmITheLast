#include <SFML/Graphics.hpp>
#include "AssetImporter.h"
#ifndef ENTITY_H
#define ENTITY_H
class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Update(const float& dt)=0;
	virtual void Render(sf::RenderTarget* target)=0;

protected:
	float MovementSpeed = 0;
	sf::Texture Texture;
	sf::Sprite Sprite;
};
#endif

