#include <SFML/Graphics.hpp>
#include "Utilitary/AssetImporter.h"
#include"Components/MapGenerator.h"

#ifndef TILEMAP_H
#define TILEMAP_H

class TileMap:public sf::Drawable, public sf::Transformable
{
public:
	TileMap( sf::Texture &texture,MapGenerator* mapGenerator);
	virtual ~TileMap();
private:

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Texture* Texture;
	sf::VertexArray VertexArray;
	MapGenerator* MapGen;
};


#endif