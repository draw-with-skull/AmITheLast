#include "MapGenerator.h"


MapGenerator::MapGenerator(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight)
{
    
    srand((unsigned int)time(NULL));
    this->FloorTiles = 0;
    this->RoomsConnections.clear();
    this->SetRoomsSize(3, 5, 3, 5);
    this->MapH = height;
    this->MapW = width;
    this->TileH = tileHeight;
    this->TileW = tileWidth;
    this->BufferSize = MapH * MapW;
    this->Map = new int[BufferSize];
    //reset all values in the map
    for (unsigned int i = 0; i < this->BufferSize; i++) {
        this->Map[i] = BLANK;
    }
}

MapGenerator::~MapGenerator()
{
    delete this->Map;
}

int* MapGenerator::Generate()
{
    this->GenerateDefaultTileMapping();

    this->GenerateFloor();
    this->FixFloors();

    this->GenerateWalls();
    this->GetFloorTilesCount();
    return Map;
}

void MapGenerator::MapTiles(std::map<MAPCOMPONENTS, sf::Vector2f> mapping)
{
    this->Tilemapping = mapping;
}

sf::Vector2u MapGenerator::GetTileSize()
{
    return sf::Vector2u(this->TileW, this->TileH);
}

sf::Vector2i MapGenerator::GetMapSize()
{
    return sf::Vector2i(this->MapW,this->MapH);
}

sf::Vector2f MapGenerator::GetSpownPosition()
{

    sf::Vector2u Position = RoomsConnections[rand() % RoomsCount];
    
    return sf::Vector2f((float)(Position.y * TileH + (TileH / 2)), (float)(Position.x * TileW + (TileW / 2)));
}

unsigned int MapGenerator::GetBufferSize()
{
    return this->BufferSize;
}

void MapGenerator::SetRoomsSize(unsigned int minRoomH, unsigned int maxRoomH, unsigned int minRoomW, unsigned int maxRoomW)
{
    this->MinRoomH = minRoomH;
    this->MaxRoomH = maxRoomH;
    this->MinRoomW = minRoomW;
    this->MaxRoomW = maxRoomW;
}

void MapGenerator::GenerateFloor()
{
    this->RoomsCount =  rand() % (MapW/2) + 5;
    sf::Vector2i RoomSize, RoomPosition;

    //generate Rooms at randome 
    for (int i = 0; i < RoomsCount; i++)
    {
        
        RoomSize.x = rand() % (MaxRoomH-MinRoomH) +MinRoomH;
        RoomSize.y = rand() % (MaxRoomW-MinRoomW) +MinRoomW;

        if (RoomSize.x < 3)RoomSize.x += 3;
        if (RoomSize.y < 3)RoomSize.y += 3;

        RoomPosition.x = rand() % (int)MapH+1 ;
        RoomPosition.y = rand() % (int)MapW+1 ;

        if (RoomPosition.x + RoomSize.x > (int)MapW)RoomPosition.x -= RoomSize.x+2;
        if (RoomPosition.y + RoomSize.y > (int)MapW)RoomPosition.y -= RoomSize.y+2;

        this->RoomsConnections.push_back(sf::Vector2u(RoomPosition.x+(RoomSize.x/2), RoomPosition.y + (RoomSize.x / 2)));
        this->Rooms.push_back(sf::IntRect(RoomPosition, RoomSize));

        for (int i = 0;i<RoomSize.x;i++)
            for (int j =0; j < RoomSize.y; j++)
            {
                int row = ((MapW * RoomPosition.x) + RoomPosition.y)+i*MapW;
                this->Map[row+j] = FLOOR;
            }
    }
    //Generate corridors

    for (int i = 0; i < RoomsConnections.size()-1; i++) {

        this->Map[RoomsConnections[i].x * MapW + RoomsConnections[i].y] = FLOOR;
        this->Map[RoomsConnections[i+1].x * MapW + RoomsConnections[i+1].y] = FLOOR;

        this->GenerateCorridors(RoomsConnections[i], RoomsConnections[i + 1]);

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
                    this->Map[i + j * MapW] = FLOOR;
                if (Map[(i + j * MapW) - 1] == FLOOR && Map[(i + j * MapW) + 1] == FLOOR)
                    this->Map[i + j * MapW] = FLOOR;
            }
        }
    //Generation bugs
    for (unsigned int i = 0; i < MapH; i++) {
        this->Map[MapW * i+MapW-1] = BLANK;
    }
    for (unsigned int i = 0; i < MapH; i++) {
        this->Map[MapW * (MapW - 1)+i] = BLANK;
    }

}

void MapGenerator::GetFloorTilesCount()
{
    for (unsigned int i = 0; i < BufferSize; i++) {
        if (Map[i] == FLOOR) {
            this->FloorTiles++;
        }
    }
}

void MapGenerator::GenerateCorridors(sf::Vector2u startPoint, sf::Vector2u endPoint)
{
    //x e in jos si y e la dreapta 
    
    
    int FinalPoint=0;

    if (startPoint.y < endPoint.y) {
        for (unsigned int i = 0; i <= endPoint.y - startPoint.y; i++) {
            this->Map[MapW * startPoint.x + startPoint.y +i] = FLOOR;
            FinalPoint = startPoint.y+ i;
        }
    }
    else {
        for (unsigned int i = 0; i <= startPoint.y-endPoint.y; i++) {
            this->Map[MapW * endPoint.x + endPoint.y + i] = FLOOR;
            FinalPoint = endPoint.y+ i;
        }
    }

    if (startPoint.x < endPoint.x) {
        for (unsigned int i = 0; i < endPoint.x - startPoint.x; i++) {
            this->Map[MapW *(i+startPoint.x) + FinalPoint] = FLOOR;
        }
    }
    else {
        for (unsigned int i = 0; i < startPoint.x - endPoint.x; i++) {
            this->Map[MapW * (i+endPoint.x) + FinalPoint] = FLOOR;
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