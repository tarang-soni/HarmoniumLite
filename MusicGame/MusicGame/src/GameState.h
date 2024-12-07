#pragma once
#include "State.h"
#include "UIElement.h"
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Scene.h"
class GameState :
    public State
{
    // Inherited via State
public:
    GameState(StateStack& stateStack, Context context);
    void Enter() override;
    bool Update() override;
    bool Render(sf::RenderTarget& target) override;
    bool HandleEvent(const sf::Event& event) override;
    void Exit() override;

    void GoToMenu();
    std::vector<std::unique_ptr<UIElement>> uiElements;
private:
    sf::Color _bgColor;
    Scene _scene;
};
