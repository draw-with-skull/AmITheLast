#include "MapGenerator.h"






MapGenerator::MapGenerator(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight)
{
    srand((unsigned int)time(NULL));

    this->MapH = height;
    this->MapW = width;
    this->TileH = tileHeight;
    this->TileW = tileWidth;
    this->BufferSize = MapH * MapW;
    this->Map = new int[BufferSize];
    //reset all values in the map
    for (unsigned int i = 0; i < this->BufferSize; i++) {
        Map[i] = BLANK;
    }
}

int* MapGenerator::Generate()
{
    GenerateDefaultTileMapping();

    GenerateFloor();
    return Map;
}

void MapGenerator::MapTiles(std::map<MAPCOMPONENTS, sf::Vector2f> mapping)
{
    this->Tilemapping = mapping;
}

sf::Vector2u MapGenerator::GetTileSize()
{
    return sf::Vector2u(this->TileH,this->TileW);
}

sf::Vector2i MapGenerator::GetMapSize()
{
    return sf::Vector2i(this->MapH,this->MapW);
}

unsigned int MapGenerator::GetBufferSize()
{
    return this->BufferSize;
}


void MapGenerator::GenerateDefaultTileMapping()
{
    Tilemapping[FLOOR] = sf::Vector2f(1, 1);
    Tilemapping[BLANK] = sf::Vector2f(0,3);

    Tilemapping[BOTTOM_WALL] = sf::Vector2f(1, 2);
    Tilemapping[TOP_WALL] = sf::Vector2f(1,0);
    Tilemapping[LEFT_WALL] = sf::Vector2f(0, 1);
    Tilemapping[RIGHT_WALL] = sf::Vector2f(2, 1);

    Tilemapping[BOTTOM_LEFT_CORNER] = sf::Vector2f(0,2);
    Tilemapping[BOTTOM_RIGHT_CONRNER] = sf::Vector2f(2,2);
    Tilemapping[TOP_LEFT_CORNER] = sf::Vector2f(0,0);
    Tilemapping[TOP_RIGHT_CORNER] = sf::Vector2f(2,0);

    Tilemapping[LEFT_BOTTOM_CORNER] = sf::Vector2f(1,3);
    Tilemapping[LEFT_TOP_CORNER] = sf::Vector2f(2,2);
    Tilemapping[RIGHT_BOTTOM_CORNER] = sf::Vector2f(2,3);
    Tilemapping[RIGHT_TOP_CORNER] = sf::Vector2f(0,2);

}

void MapGenerator::GenerateFloor()
{
}
