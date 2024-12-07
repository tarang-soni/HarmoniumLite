#include "GameState.h"
#include "UIFactory.h"
#include <iostream>
#include "CallbackRegistry.h"
#include "StateStack.h"
#include <string>
#include "Core.h"
GameState::GameState(StateStack& stateStack, Context context)
	:State(stateStack,context),
	uiElements(),
	_bgColor(),
	_scene(*context.window)
{
	using Registry = CallbackRegistry<GameState>;
	Registry::RegisterCallback<&GameState::GoToMenu>("MainMenu");
}

void GameState::Enter()
{
	const char* path = "example.json";
	const char* screenType = "Game";
	uiElements = UIFactory::CreateAllElements(screenType, path, *this);
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error("Cannot open file: " + std::string(path));
	}
	nlohmann::json data = nlohmann::json::parse(file);
	_bgColor = hexToColor(data[screenType]["bgColor"]);
	std::cout << "Enter menu" << std::endl;
}

bool GameState::Update()
{
	_scene.Update();
	for (auto& element : uiElements)
	{
		element->Update(*_context.window);
	}

	return false;
}

bool GameState::Render(sf::RenderTarget& target)
{
	target.clear(_bgColor);
	_scene.Render(target);
	for (auto& element : uiElements)
	{
		element->draw(target, sf::RenderStates::Default);
	}
	return false;
}

bool GameState::HandleEvent(const sf::Event& _event)
{
	_scene.PollEvents(_event);
	for (auto& element : uiElements)
	{
		element->HandleEvents(_event, *_context.window);
	}
	return false;
}
void GameState::GoToMenu()
{
	std::cout << "Working" << std::endl;
	_stateStack->PopState();
	_stateStack->PushState(States::Menu);
}
void GameState::Exit()
{
}
