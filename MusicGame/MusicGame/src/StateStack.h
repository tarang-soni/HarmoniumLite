#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include <vector>
#include <memory>
#include "State.h"
#include "StateIdentifiers.h"
class StateStack :private sf::NonCopyable {
public:
	enum Action {
		Push,
		Pop,
		Clear
	};
public:
	explicit StateStack(State::Context context);
	template<typename T>
	void RegisterStates(States::ID type);

	void Update();
	void Render(sf::RenderTarget& target);
	void HandleEvent(const sf::Event& event);

	void PushState(States::ID stateID);
	void PopState();
	void ClearStates();

	bool IsEmpty() const;
private:
	State::Ptr CreateState(States::ID stateID);
	void ApplyPendingChanges();

private:
	struct PendingChange 
	{
		explicit PendingChange(Action action, States::ID stateID = States::None);
		Action action;
		States::ID stateID;
	};
private:
	std::vector<State::Ptr> mStack;
	std::vector<PendingChange> mPendingList;
	std::map <States::ID, std::function<State::Ptr()>> mFactories;
	State::Context _context;
};
template<typename T>
void StateStack::RegisterStates(States::ID type) 
{
	mFactories[type] = [this]()
		{
			return State::Ptr(new T(*this,_context));
		};
}