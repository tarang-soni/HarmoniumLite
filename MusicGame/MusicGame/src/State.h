#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
class StateStack;
class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context {
	public:
		sf::RenderWindow* window;
		 Context(sf::RenderWindow& win) 
			:window(&win) 
		{

		}

	};
public:
	State(StateStack& stateStack,Context context):_stateStack(&stateStack),_context(context){}
	virtual ~State(){}
	virtual void Enter() = 0;
	virtual bool Update() = 0;
	virtual bool Render(sf::RenderTarget& target) = 0;
	virtual bool HandleEvent(const sf::Event& event) = 0;
	virtual void Exit() = 0;

protected:
	StateStack* _stateStack;
	Context _context;
};