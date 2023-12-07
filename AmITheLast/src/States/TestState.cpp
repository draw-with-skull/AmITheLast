#include "TestState.h"
#include <SFML/Window/Mouse.hpp>

TestState::TestState(sf::RenderWindow* window, sf::View *view):State(window)
{
	this->View = view;
	this->window = window;
	this->RoomTexture = AssetImporter().ImportTexture("Dangeon", AssetType::ROOM);
	this->MapG = new MapGenerator(32,32, 32, 32);
	this->Room = new TileMap(this->RoomTexture,MapG);
	this->Collisions = this->MapG->GetColisions();
	this->Player.SetPosition(MapG->GetSpownPosition());
	this->Player.SetHitBox(12, 16, 0, 8);
	this->Player.SetLegHitBox(12, 4, 0, 14);
}

TestState::~TestState()
{
	delete this->MapG;
	delete this->Room;
}

void TestState::Update(const float& dt)
{
	this->CheckForQuit();
	this->UpdateKeyBinds(dt);
	this->Player.Update(dt);
	this->View->setCenter(this->Player.GetPosition());
	if (Intersection::Check(Player.GetLegHitBox(), Collisions)) {
		printf("collision\n");
	}
	else {
		printf("no collision\n");
	}
	
}

void TestState::Render(sf::RenderTarget* target)
{
	if (target == NULL)target = this->window;
	target->setView(*View);
	target->draw(*this->Room);
	this->Player.Render(target);
	sf::RectangleShape r;
	for (int i = 0; i < Collisions.size(); i++) {
		r.setSize(Collisions[i].getSize());
		r.setPosition(Collisions[i].getPosition());
		r.setFillColor(sf::Color::Red);
		target->draw(r);
	}


}


void TestState::UpdateKeyBinds(const float& dt)
{
}

