#include "MapGenerator.h"


MapGenerator::MapGenerator(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight)
{
    
    srand((unsigned int)time(NULL));
    FloorTiles = 0;
    RoomsConnections.clear();
    this->SetRoomsSize(3, 5, 3, 5);
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

MapGenerator::~MapGenerator()
{
    delete this->Map;
}

int* MapGenerator::Generate()
{
    GenerateDefaultTileMapping();

    GenerateFloor();
    FixFloors();
    GetFloorTiles();

    GenerateWalls();
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

sf::Vector2f MapGenerator::GetSpownPosition()
{
    return sf::Vector2f();
}

unsigned int MapGenerator::GetBufferSize()
{
    return this->BufferSize;
}

void MapGenerator::SetRoomsSize(unsigned int MinRoomH, unsigned int MaxRoomH, unsigned int MinRoomW, unsigned int MaxRoomW)
{
    this->MinRoomH = MinRoomH;
    this->MaxRoomH = MaxRoomH;
    this->MinRoomW = MinRoomW;
    this->MaxRoomW = MaxRoomW;
}

void MapGenerator::GenerateFloor()
{
    int RoomsCount =  rand() % (MapW/2) + 5;

    //generate Rooms at randome 
    for (int i = 0; i < RoomsCount; i++)
    {
        sf::Vector2i RoomSize, RoomPosition;
        RoomSize.x = rand() % MaxRoomH + MinRoomH;
        RoomSize.y = rand() % MaxRoomW + MinRoomW;

        if (RoomSize.x < 3)RoomSize.x += 3;
        if (RoomSize.y < 3)RoomSize.y += 3;

        RoomPosition.x = rand() % (int)MapH+1 ;
        RoomPosition.y = rand() % (int)MapW+1 ;

        if (RoomPosition.x + RoomSize.x > (int)MapW)RoomPosition.x -= RoomSize.x+2;
        if (RoomPosition.y + RoomSize.y > (int)MapW)RoomPosition.y -= RoomSize.y+2;

        RoomsConnections.push_back(sf::Vector2u(RoomPosition.x+(RoomSize.x/2), RoomPosition.y + (RoomSize.x / 2)));

        for (int i = 0;i<RoomSize.x;i++)
            for (int j =0; j < RoomSize.y; j++)
            {
                int row = ((MapW * RoomPosition.x) + RoomPosition.y)+i*MapW;
                Map[row+j] = FLOOR;
            }
    }
    //Generate corridors

    for (int i = 0; i < RoomsConnections.size()-1; i++) {

        Map[RoomsConnections[i].x * MapW + RoomsConnections[i].y] = FLOOR;
        Map[RoomsConnections[i+1].x * MapW + RoomsConnections[i+1].y] = FLOOR;

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
    for (unsigned int i = 0; i < MapH; i++) {
        Map[MapW * i+MapW-1] = BLANK;
    }
}

void MapGenerator::GetFloorTiles()
{
    for (unsigned int i = 0; i < BufferSize; i++) {
        if (Map[i] == FLOOR) {
            FloorTiles++;
        }
    }
    std::cout << FloorTiles;
}

void MapGenerator::GenerateCorridors(sf::Vector2u StartPoint, sf::Vector2u EndPoint)
{
    //x e in jos si y e la dreapta 
    
    
    int FinalPoint=0;

    if (StartPoint.y < EndPoint.y) {
        for (unsigned int i = 0; i <= EndPoint.y - StartPoint.y; i++) {
            Map[MapW * StartPoint.x + StartPoint.y +i] = FLOOR;
            FinalPoint = StartPoint.y+ i;
        }
    }
    else {
        for (unsigned int i = 0; i <= StartPoint.y-EndPoint.y; i++) {
            Map[MapW * EndPoint.x + EndPoint.y + i] = FLOOR;
            FinalPoint = EndPoint.y+ i;
        }
    }

    if (StartPoint.x < EndPoint.x) {
        for (unsigned int i = 0; i < EndPoint.x - StartPoint.x; i++) {
            Map[MapW *(i+StartPoint.x) + FinalPoint] = FLOOR;
        }
    }
    else {
        for (unsigned int i = 0; i < StartPoint.x - EndPoint.x; i++) {
            Map[MapW * (i+EndPoint.x) + FinalPoint] = FLOOR;
        }
    }
    
}

void MapGenerator::GenerateWalls()
{
    for(unsigned int i=1;i<MapW-1;i++)
        for(unsigned int j=1;j<MapH-1;j++)
        {
            
            if (Map[i + j * MapW] == FLOOR)
            {
                //Walls
                
                if (Map[(i + j * MapW) - 1] == BLANK)
                {
                    Map[(i + j * MapW) - 1] = LEFT_WALL;
                }
                if (Map[(i + j * MapW) + 1] == BLANK)
                {
                    Map[(i + j * MapW) + 1] = RIGHT_WALL;
                }
                if (Map[(i + j * MapW) - MapW] == BLANK)
                {
                    Map[(i + j * MapW) - MapW] = TOP_WALL;
                }
                if (Map[(i + j * MapW) + MapW] == BLANK)
                {
                    Map[(i + j * MapW) + MapW] = BOTTOM_WALL;
                }
                //topcorners
                if (Map[(i + j * MapW) - 1 - MapW] == BLANK)
                {
                    Map[(i + j * MapW) - 1 - MapW] = TOP_LEFT_CORNER;
                }
                if (Map[(i + j * MapW) + 1 - MapW] == BLANK && Map[(i + j * MapW) + 1] != FLOOR)
                {
                    Map[(i + j * MapW) + 1 - MapW] = TOP_RIGHT_CORNER;
                }
                //bottom corners
                if (Map[(i + j * MapW) - 1 + MapW] == BLANK&& Map[(i + j * MapW) +MapW]!=FLOOR) {
                    Map[(i + j * MapW) - 1 + MapW]= RIGHT_TOP_CORNER;
                }
                if (Map[(i + j * MapW) + 1 + MapW] == BLANK && Map[(i + j * MapW) + 1] != FLOOR && Map[(i + j * MapW) + MapW] != FLOOR) {
                    Map[(i + j * MapW) + 1 + MapW] = LEFT_TOP_CORNER;
                }
                if (Map[(i + j * MapW) + 1] == FLOOR && Map[(i + j * MapW) + MapW] == FLOOR&& Map[(i + j * MapW) + 1 + MapW]!=FLOOR) {
                    Map[(i + j * MapW) + 1 + MapW] = RIGHT_BOTTOM_CORNER;
                }
                if (Map[(i + j * MapW) - 1] == FLOOR && Map[(i + j * MapW) + MapW] == FLOOR && Map[(i + j * MapW) - 1 + MapW] != FLOOR) {
                    Map[(i + j * MapW) - 1 + MapW] = LEFT_BOTTOM_CORNER;
                }




               
            }
            
            //Nasty Wall Bug; Temp fix
            if (Map[(i + j * MapW)] == RIGHT_WALL && Map[(i + j * MapW)-1] == FLOOR&& Map[(i + j * MapW) +MapW]==FLOOR)
            {
                Map[(i + j * MapW)] = TOP_WALL;
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