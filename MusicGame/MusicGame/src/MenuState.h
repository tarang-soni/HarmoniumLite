#pragma once
#include "State.h"
#include "UIElement.h"
#include <vector>
#include <memory>
class MenuState :
    public State
{
public:

    // Inherited via State
    MenuState(StateStack& stateStack,Context context);
    void Enter() override;
    bool Update() override;
    bool Render(sf::RenderTarget& target) override;
    bool HandleEvent(const sf::Event& event) override;
    void Exit() override;
    void StartGame();
    std::vector<std::unique_ptr<UIElement>> uiElements;

private:
    sf::Color _bgColor;
};

