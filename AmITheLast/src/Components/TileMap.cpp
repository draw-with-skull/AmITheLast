#include "TileMap.h"



TileMap::TileMap(sf::Texture& texture, MapGenerator* mapGenerator)
{
    this->Texture = &texture;
    this->VertexArray.setPrimitiveType(sf::Quads);
    this->MapGen = mapGenerator;
    this->VertexArray.resize(static_cast<size_t>(this->MapGen->GetBufferSize()) * 6);// two triangles per tile

    sf::Vector2u TileSize = this->MapGen->GetTileSize();
    sf::Vector2i MapSize = this->MapGen->GetMapSize();
    int* Map = this->MapGen->Generate();

    for ( int i = 0; i < MapSize.x; ++i)
        for ( int j = 0; j < MapSize.y; ++j)
        {
            // get the current tile number

            //// get a pointer to the current tile's quad
            sf::Vertex* quad = &VertexArray[(i + static_cast<size_t>(j) * MapSize.x) * 4];

            ////// define its 4 corners
            quad[0].position = sf::Vector2f(i * (float)TileSize.x, j * (float)TileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * (float)TileSize.x, j * (float)TileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * (float)TileSize.x, (j + 1) * (float)TileSize.y);
            quad[3].position = sf::Vector2f(i * (float)TileSize.x, (j + 1) * (float)TileSize.y);

            //extract tile UV
            sf::Vector2f Mapping = MapGen->Tilemapping.at(static_cast<MapGenerator::MAPCOMPONENTS>(Map[i + j * MapSize.x]));
            Mapping.x = Mapping.x * TileSize.x;
            Mapping.y = Mapping.y * TileSize.y;

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(Mapping);
            quad[1].texCoords = sf::Vector2f(Mapping.x+TileSize.x, Mapping.y);
            quad[2].texCoords = sf::Vector2f(Mapping.x+TileSize.y, Mapping.y + TileSize.y);
            quad[3].texCoords = sf::Vector2f(Mapping.x,Mapping.y+TileSize.y);
        }
    
}

TileMap::~TileMap()
{
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = Texture;

        // draw the vertex array
        target.draw(VertexArray, states);
}
