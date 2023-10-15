#include "TestState.h"
#include <iostream>
TestState::TestState(sf::RenderWindow* window):State(window)
{
}

TestState::~TestState()
{
}

void TestState::Update(const float& dt)
{
	this->CheckForQuit();
	this->UpdateKeyBinds(dt);
	this->player.Update(dt);

}

void TestState::Render(sf::RenderTarget* target)
{
	if (target == NULL)target = this->window;
	
	this->player.Render(target);
}


void TestState::UpdateKeyBinds(const float& dt)
{
}

