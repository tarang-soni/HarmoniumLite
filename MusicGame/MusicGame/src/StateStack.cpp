#include "StateStack.h"
#include <cassert>

StateStack::StateStack(State::Context context)
	:mStack(),
	mPendingList(),
	mFactories(),
    _context(context)
{
}

void StateStack::Update()
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) 
	{
		if (!(*itr)->Update())
			break;
	}
	ApplyPendingChanges();
}

void StateStack::Render(sf::RenderTarget& target)
{
	for (auto& state : mStack)
	{
		state->Render(target);
	}
}

void StateStack::HandleEvent(const sf::Event& event)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->HandleEvent(event))
			break;
	}
	ApplyPendingChanges();
}

void StateStack::PushState(States::ID stateID)
{
	mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::PopState()
{
	mPendingList.push_back(PendingChange(Pop));
}

void StateStack::ClearStates()
{
	mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::IsEmpty() const
{
	return mStack.empty();
}

State::Ptr StateStack::CreateState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());
	
	return found->second();
}

void StateStack::ApplyPendingChanges()
{
    for (auto& change : mPendingList)
    {
        switch (change.action)
        {
        case Push:
        {
            // Scoped block for variables in this case
            State::Ptr newState = CreateState(change.stateID);

            // Optional: Pre-push logic
            if (newState)
            {
                newState->Enter(); // Example pre-push method
            }

            mStack.push_back(std::move(newState));
            break;
        }

        case Pop:
        {
            // Scoped block for variables in this case
            if (!mStack.empty())
            {
                State::Ptr removedState = std::move(mStack.back());
                mStack.pop_back();

                // Optional: Post-pop logic
                if (removedState)
                {
                    removedState->Exit(); // Example post-pop method
                }
            }
            break;
        }

        case Clear:
        {
            // Scoped block for clear logic
            mStack.clear();
            break;
        }

        default:
            break; // Handle unexpected actions
        }
    }

    // Clear the pending changes after applying them
    mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID):action(action),stateID(stateID)
{
}
