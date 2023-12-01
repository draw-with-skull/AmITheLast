#include "MapGenerator.h"


MapGenerator::MapGenerator(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight)
{
    srand((unsigned int)time(NULL));
    RoomsConnections.clear();
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
    //FixFloors();
    //GenerateWalls();
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




void MapGenerator::GenerateFloor()
{
    int RoomsCount = 5;// rand() % 5 + 5;

    //generate Rooms at randome 
    for (int i = 0; i < RoomsCount; i++)
    {
        sf::Vector2i RoomSize, RoomPosition;
        RoomSize.x = rand() % ((int)MapH / 3);
        RoomSize.y = rand() % ((int)MapW / 3);

        if (RoomSize.x < 3)RoomSize.x += 3;
        if (RoomSize.y < 3)RoomSize.y += 3;

        RoomPosition.x = rand() % (int)MapH+1 ;
        RoomPosition.y = rand() % (int)MapW+1 ;

        if (RoomPosition.x + RoomSize.x > (int)MapW)RoomPosition.x -= RoomSize.x;
        if (RoomPosition.y + RoomSize.y > (int)MapW)RoomPosition.y -= RoomSize.y;

        RoomsConnections.push_back(sf::Vector2u(RoomPosition.x+(RoomSize.x/2), RoomPosition.y + (RoomSize.x / 2)));

        for (int i = 0;i<RoomSize.x;i++)
            for (int j =0; j < RoomSize.y; j++)
            {
                int row = ((MapW * RoomPosition.x) + RoomPosition.y)+i*MapW;
                Map[row+j] = FLOOR;
            }
    }
    //Generate corridors
    std::cout << RoomsConnections.size() << "\n";

    for (int i = 0; i < RoomsConnections.size()-1; i++) {
      
        //std::cout << RoomsConnections[i].x << " " << RoomsConnections[i].x << " ";
        //std::cout << RoomsConnections[i].x * MapW + RoomsConnections[i].y << "\n";
        Map[RoomsConnections[i].x * MapW + RoomsConnections[i].y] = NO_TEXTURE;
        Map[RoomsConnections[i+1].x * MapW + RoomsConnections[i+1].y] = NO_TEXTURE;

        GenerateCorridors(RoomsConnections[i], RoomsConnections[i + 1]);

    }

}



void MapGenerator::FixFloors()
{
    for (unsigned int i = 1; i < MapW-1; i++)
        for (unsigned int j = 1; j < MapH-1; j++)
        {
            //1 tile gap between rooms
            if (Map[i + j * MapW] != FLOOR) {
                if (Map[(i + j * MapW) - MapW] == FLOOR && Map[(i + j * MapW) + MapW] == FLOOR)
                    Map[i + j * MapW] = FLOOR;
                if (Map[(i + j * MapW) - 1] == FLOOR && Map[(i + j * MapW) + 1] == FLOOR)
                    Map[i + j * MapW] = FLOOR;
            }
        }
}

void MapGenerator::GenerateCorridors(sf::Vector2u StartPoint, sf::Vector2u EndPoint)
{
    if (StartPoint.x > EndPoint.y) {
        //<-
        if (StartPoint.y > EndPoint.y) {
            //to top
        }
        else {
            //to bottom
        }
    }
    else {
        //->
        if (StartPoint.y > EndPoint.y) {
            //to top
        }
        else {
            //to bottom
        }
    }
}

void MapGenerator::GenerateWalls()
{
    for(unsigned int i=0;i<MapW;i++)
        for(unsigned int j=0;j<MapH;j++)
        {
            
            if (Map[i + j * MapW] == FLOOR)
            {
                //Walls
                if (Map[(i + j * MapW) - MapW] == BLANK)
                    Map[(i + j * MapW) - MapW] = TOP_WALL;

                if (Map[(i + j * MapW) + MapW] == BLANK)
                    Map[(i + j * MapW) + MapW] = BOTTOM_WALL;

                if (Map[(i + j * MapW) - 1] == BLANK)
                    Map[(i + j * MapW) - 1] = LEFT_WALL;

                if (Map[(i + j * MapW) + 1] == BLANK)
                    Map[(i + j * MapW) + 1] = RIGHT_WALL;
                //Corners

                if (Map[(i + j * MapW) - 1 - MapW] == BLANK)
                  Map[(i + j * MapW) - 1 - MapW] = TOP_LEFT_CORNER;

                if (Map[(i + j * MapW) + 1 - MapW] == BLANK && Map[(i + j * MapW) + 1]!= FLOOR)
                    Map[(i + j * MapW) + 1 - MapW] = TOP_RIGHT_CORNER;

                //if (Map[(i + j * MapW) - 1 + MapW] == BLANK)
                //    Map[(i + j * MapW) - 1 + MapW] = BOTTOM_LEFT_CORNER;

                //if (Map[(i + j * MapW) + 1 + MapW] == BLANK && Map[(i + j * MapW) - 1] != FLOOR)
                //    Map[(i + j * MapW) + 1 + MapW] = BOTTOM_RIGHT_CONRNER;
            }
        }
}

void MapGenerator::GenerateDefaultTileMapping()
{
    Tilemapping[FLOOR] = sf::Vector2f(1, 1);
    Tilemapping[BLANK] = sf::Vector2f(0, 3);

    Tilemapping[BOTTOM_WALL] = sf::Vector2f(1, 2);
    Tilemapping[TOP_WALL] = sf::Vector2f(1, 0);
    Tilemapping[LEFT_WALL] = sf::Vector2f(0, 1);
    Tilemapping[RIGHT_WALL] = sf::Vector2f(2, 1);

    Tilemapping[BOTTOM_LEFT_CORNER] = sf::Vector2f(0, 2);
    Tilemapping[BOTTOM_RIGHT_CONRNER] = sf::Vector2f(2, 2);
    Tilemapping[TOP_LEFT_CORNER] = sf::Vector2f(0, 0);
    Tilemapping[TOP_RIGHT_CORNER] = sf::Vector2f(2, 0);

    Tilemapping[LEFT_BOTTOM_CORNER] = sf::Vector2f(1, 3);
    Tilemapping[LEFT_TOP_CORNER] = sf::Vector2f(2, 2);
    Tilemapping[RIGHT_BOTTOM_CORNER] = sf::Vector2f(2, 3);
    Tilemapping[RIGHT_TOP_CORNER] = sf::Vector2f(0, 2);
    Tilemapping[NO_TEXTURE] = sf::Vector2f(5,7);
}