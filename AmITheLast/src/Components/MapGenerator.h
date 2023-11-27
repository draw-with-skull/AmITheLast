#pragma once
#include <time.h>  
#include <stdlib.h>
#include <map>
#include <SFML/System/Vector2.hpp>
#include <iostream>
class MapGenerator
{
public:
    enum MAPCOMPONENTS {
        BLANK,
        FLOOR,
        //WALLS
        TOP_WALL,
        BOTTOM_WALL,
        LEFT_WALL,
        RIGHT_WALL,
        //CONERS OUTSIDE
        TOP_LEFT_CORNER,
        TOP_RIGHT_CORNER,
        BOTTOM_LEFT_CORNER,
        BOTTOM_RIGHT_CONRNER,
        //CORNERS INSIDE
        LEFT_TOP_CORNER,
        RIGHT_TOP_CORNER,
        LEFT_BOTTOM_CORNER,
        RIGHT_BOTTOM_CORNER
    };

    MapGenerator(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight);
	int* Generate();
	void MapTiles(std::map<MAPCOMPONENTS,sf::Vector2f>mapping);

    sf::Vector2u GetTileSize();
    sf::Vector2i GetMapSize();
    unsigned int GetBufferSize();

    std::map<MAPCOMPONENTS, sf::Vector2f> Tilemapping;

private:
    void GenerateDefaultTileMapping();
	void GenerateFloor();
    unsigned int MapH, MapW ,BufferSize;
    unsigned int TileW, TileH;
    
	int* Map;

};

