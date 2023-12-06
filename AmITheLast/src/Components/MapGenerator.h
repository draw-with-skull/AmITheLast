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
    void SetRoomsSize(unsigned int minRoomH, unsigned int maxRoomH, unsigned int minRoomW, unsigned int maxRoomW);

    std::map<MAPCOMPONENTS, sf::Vector2f> Tilemapping;

private:
	void GenerateFloor();
    void FixFloors();
    void GetFloorTilesCount();
    void GenerateCorridors(sf::Vector2u startPoint, sf::Vector2u endPoint);
    void GenerateWalls();
    void GenerateDefaultTileMapping();

    unsigned int MinRoomH, MaxRoomH, MinRoomW, MaxRoomW;
    unsigned int BufferSize, FloorTiles;
    unsigned int MapH, MapW;
    unsigned int TileW, TileH;

    int RoomsCount;
	int* Map;
    sf::IntRect* Collisions;
    std::vector<sf::Vector2u> RoomsConnections;
    std::vector<sf::IntRect>Rooms;

};

