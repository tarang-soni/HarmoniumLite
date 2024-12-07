#include "MenuState.h"
#include "UIFactory.h"
#include <iostream>
#include "CallbackRegistry.h"
#include "StateStack.h"
#include <string>
#include "Core.h"
MenuState::MenuState(StateStack& stateStack,Context context):State(stateStack,context)
{
	using Registry = CallbackRegistry<MenuState>;
	Registry::RegisterCallback<&MenuState::StartGame>("StartGame");
}
void MenuState::Enter()
{
	const char* path = "example.json";
	const char* screenType = "Menu";
	uiElements = UIFactory::CreateAllElements(screenType, path, *this);
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error("Cannot open file: " + std::string(path));
	}
	nlohmann::json data = nlohmann::json::parse(file);
	_bgColor = hexToColor(data[screenType]["bgColor"]);
	std::cout << "Enter menu" << std::endl;
}

bool MenuState::Update()
{
	for (auto& element : uiElements)
	{
		element->Update(*_context.window);
	}
	return false;
}

bool MenuState::Render(sf::RenderTarget& target)
{
	target.clear(_bgColor);
	for (auto& element : uiElements)
	{
		element->draw(target,sf::RenderStates::Default);
	}
	return false;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
	for (auto& element : uiElements)
	{
		element->HandleEvents(event,*_context.window);
	}
	return false;
}

void MenuState::Exit()
{
}

void MenuState::StartGame()
{
	std::cout << "Working"<<std::endl;
	_stateStack->PopState();
	_stateStack->PushState(States::Game);
}
