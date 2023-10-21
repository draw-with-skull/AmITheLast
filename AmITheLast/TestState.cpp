#include "TestState.h"
#include <iostream>
TestState::TestState(sf::RenderWindow* window, sf::View *view):State(window)
{
	this->View = view;
}

TestState::~TestState()
{
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
	this->Player.Render(target);
}


void TestState::UpdateKeyBinds(const float& dt)
{
}

