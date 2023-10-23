#include "TestState.h"


TestState::TestState(sf::RenderWindow* window, sf::View *view):State(window)
{
	this->View = view;
	this->Level = new Room();
}

TestState::~TestState()
{
}

void TestState::Update(const float& dt)
{
	this->CheckForQuit();
	this->UpdateKeyBinds(dt);
	this->Level->Update();
	this->Player.Update(dt);
	this->View->setCenter(this->Player.GetPosition());

}

void TestState::Render(sf::RenderTarget* target)
{
	if (target == NULL)target = this->window;
	target->setView(*View);
	this->Level->Render(target);
	this->Player.Render(target);
}


void TestState::UpdateKeyBinds(const float& dt)
{
}

