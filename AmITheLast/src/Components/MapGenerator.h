#pragma once
#include <time.h>  
#include <stdlib.h>
#include <map>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
class MapGenerator
{
public:
    enum MAPCOMPONENTS {
        NO_TEXTURE,
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
    virtual ~MapGenerator();
	int* Generate();
	void MapTiles(std::map<MAPCOMPONENTS,sf::Vector2f>mapping);

    sf::Vector2u GetTileSize();
    sf::Vector2i GetMapSize();
    sf::Vector2f GetSpownPosition();
    unsigned int GetBufferSize();

    std::map<MAPCOMPONENTS, sf::Vector2f> Tilemapping;

private:
	void GenerateFloor();
    void FixFloors();
    void GetFloorTiles();
    void GenerateCorridors(sf::Vector2u StartPoint, sf::Vector2u EndPoint);
    void GenerateWalls();
    void GenerateDefaultTileMapping();
    unsigned int BufferSize, FloorTiles;
    unsigned int MapH, MapW;
    unsigned int TileW, TileH;
    std::vector<sf::Vector2u> RoomsConnections;
	int* Map;

};

