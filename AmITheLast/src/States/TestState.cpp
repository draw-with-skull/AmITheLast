#include "TestState.h"


TestState::TestState(sf::RenderWindow* window, sf::View *view):State(window)
{
	this->View = view;
	this->RoomTexture = AssetImporter().ImportTexture("Dangeon", AssetType::ROOM);
	this->MapG = new MapGenerator(40, 40, 32, 32);
	this->Room = new TileMap(this->RoomTexture,MapG);
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

}

void TestState::Render(sf::RenderTarget* target)
{
	if (target == NULL)target = this->window;
	target->setView(*View);
	target->draw(*this->Room);
	this->Player.Render(target);
}


void TestState::UpdateKeyBinds(const float& dt)
{
}

