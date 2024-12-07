#include "Game.h"
//#include "State.h"
#include "MenuState.h"
#include "GameState.h"
#include <fstream>
//#include<nlohmann/json.hpp>
#include <iostream>
Game::Game(const char* name, int width, int height):
	_window(sf::VideoMode(width, height), name),
	_event(sf::Event()),
	_stateStack(_window),
	_uiFactory()
{

	RegisterStates();
	_stateStack.PushState(States::Menu);
	std::ifstream f("example.json");
	//nlohmann::json data = nlohmann::json::parse(f);
	//std::cout << data["pi"] << std::endl;
}

Game::~Game()
{
}


void Game::Run()
{

	while (_window.isOpen())
	{
		while (_window.pollEvent(_event))
		{
			switch (_event.type)
			{
			case sf::Event::Closed:
				_window.close();
				break;
			default:
				// Pass the event to the state stack for handling
				HandleInput();
				break;
			}
		}

		Update();
		if (_stateStack.IsEmpty())
			_window.close();

		Render(_window);
	}
}

void Game::RegisterStates()
{

	_stateStack.RegisterStates<MenuState>(States::Menu);
	_stateStack.RegisterStates<GameState>(States::Game);
}

void Game::HandleInput()
{
	_stateStack.HandleEvent(_event);
}

void Game::Update()
{
	_stateStack.Update();
}

void Game::Render(sf::RenderTarget& target)
{
	_window.clear(sf::Color::Blue);
	_stateStack.Render(target);
	_window.display();
}
