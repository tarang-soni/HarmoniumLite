#pragma once
#include "UIElement.h"

class Text :
    public UIElement
{
public:
    Text();
    Text(const nlohmann::json& prop);
    // Inherited via UIElement
    void SetProperties(const nlohmann::json& props) override;
    sf::Text& GetText() { return _txt; }
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Font _font;
    sf::Text _txt;
    float _fontSize;

    // Inherited via UIElement

};

