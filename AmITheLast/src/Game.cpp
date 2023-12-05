#include <iostream>
#include "Game.h"
#include "States/TestState.h"

Game::Game()
{
	this->InitWindow();
	this->InitStates();
}

Game::~Game()
{
	delete this->Window;
	while (!this->States.empty()) {
		delete this->States.top();
		this->States.pop();
	}
}

void Game::UpdateDeltaTime()
{
	this->Dt = this->Clock.restart().asSeconds();
}

void Game::UpdateSFMLEvents()
{
	while (this->Window->pollEvent(this->SfEvent))
	{
		if (this->SfEvent.type == sf::Event::Closed) {
			this->Window->close();
		}
	}
}

void Game::Render()
{
	this->Window->clear();
	if (!this->States.empty()) {
		this->States.top()->Render();
	}
	this->Window->display();
}

void Game::Update()
{
	this->UpdateSFMLEvents();
	if (!this->States.empty()) {
		this->States.top()->Update(this->Dt);



		if (this->States.top()->GetQuit()) {
			delete this->States.top();
			this->States.pop();
		}
	}
	else {
		this->Window->close();
	}
}

void Game::Run()
{
	while (this->Window->isOpen()) {
		this->UpdateDeltaTime();
		this->Update();
		this->Render();
	}
}

void Game::InitWindow()
{
	this->Window = new sf::RenderWindow(sf::VideoMode(this->WindowSize.x,this->WindowSize.y), "Knight's Dangeon");
	this->View.setSize(sf::Vector2f(this->WindowSize / this->PixelSize));
	this->View.setCenter(sf::Vector2f(this->WindowSize / this->PixelSize));
	this->Window->setView(this->View);
	this->Window->setFramerateLimit(120);
}

void Game::InitStates()
{
	this->States.push(new TestState(this->Window,&this->View));
}
