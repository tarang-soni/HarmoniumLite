#pragma once
#include <SFML/Graphics.hpp>
#include "StateStack.h"
#include "UIFactory.h"
class Game
{
public:
	Game(const char* name, int width, int height);
	~Game();
	void Run();
private:
	void RegisterStates();
	void HandleInput();
	void Update();
	void Render(sf::RenderTarget& target);
private:
	sf::RenderWindow _window;
	sf::Event _event;
	
	StateStack _stateStack;

	UIFactory _uiFactory;
};

