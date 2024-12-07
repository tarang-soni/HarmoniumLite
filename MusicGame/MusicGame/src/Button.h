#pragma once
#include "UIElement.h"
#include "Text.h"
#include <functional>

class Button :
    public UIElement
{
public:
    enum States {
        Default = 0,
        Hover,
        Pressed,
        Length
    };
public:
    Button(const nlohmann::json& prop);
    // Inherited via UIElement
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void Update(sf::RenderWindow& window) override;
    void HandleEvents(const sf::Event& e, sf::RenderWindow& window) override;
    void SetProperties(const nlohmann::json& props) override;
    bool IsHover(sf::RenderWindow& window);
    void SetOnClick(std::function<void()> onClick);
private:
    
    States currentBtnState;
    Text _txt;
    sf::RectangleShape _btn;
    sf::Color stateColors[States::Length];
    bool isPressed = false;

    std::function<void()> OnClick;
};

