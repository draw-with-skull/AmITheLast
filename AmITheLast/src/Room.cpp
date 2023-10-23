#include "Room.h"
#include<iostream>
Room::Room()
{
	this->Texture = AssetImporter().ImportTexture("Dangeon", ROOM);
	//this->SpriteSheet.setTexture(Texture);
	sf::IntRect Uvrect= sf::IntRect(0,16,16,16);


	//this->SpriteSheet.setTextureRect(Uvrect);
}
Room::~Room()
{
}

void Room::Update()
{
}

void Room::Render(sf::RenderTarget* target)
{
	sf::VertexArray vertices{ sf::Quads,4 };
	vertices[0].position = sf::Vector2f(0.f, 0.f);
	vertices[1].position = sf::Vector2f(0.f, 16.f);
	vertices[2].position = sf::Vector2f(16.f, 16.f);
	vertices[3].position = sf::Vector2f(16.f, 0.f);

	vertices[0].texCoords = sf::Vector2f(0.f, 16.f);
	vertices[1].texCoords = sf::Vector2f(0.f, 32.f);
	vertices[2].texCoords = sf::Vector2f(16.f, 32.f);
	vertices[3].texCoords = sf::Vector2f(16.f, 16.f);

	sf::VertexArray vertices1{ sf::Quads,4 };
	vertices1[0].position = sf::Vector2f(16.f, 16.f);
	vertices1[1].position = sf::Vector2f(16.f, 32.f);
	vertices1[2].position = sf::Vector2f(32.f, 32.f);
	vertices1[3].position = sf::Vector2f(32.f, 16.f);

	vertices1[0].texCoords = sf::Vector2f(0.f, 16.f);
	vertices1[1].texCoords = sf::Vector2f(0.f, 32.f);
	vertices1[2].texCoords = sf::Vector2f(16.f, 32.f);
	vertices1[3].texCoords = sf::Vector2f(16.f, 16.f);
	
	target->draw(vertices, &Texture);
	target->draw(vertices1, &Texture);
	//target->draw(this->SpriteSheet);
}

void Room::Init()
{
}

void Room::GenerateMap()
{
}

void Room::GenerateWalls()
{
}

void Room::GenerateFloor()
{
}
