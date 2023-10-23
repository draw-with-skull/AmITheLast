#ifndef ROOM_H
#define ROOM_H
#include<SFML/Graphics.hpp>
#include"Utilitary/AssetImporter.h"
class Room
{
public:
	Room();
	virtual ~Room();
	void Update();
	void Render(sf::RenderTarget* target);

private:
	void Init();
	void GenerateMap();
	void GenerateWalls();
	void GenerateFloor();
	sf::Sprite SpriteSheet;
	sf::Texture Texture;
	static const unsigned short TileCount=16;
	const unsigned short TileSize=16;
	unsigned short TileMap[TileCount][TileCount] = { 0 };
};
#endif

