#include "UIElement.h"

UIElement::UIElement():id()
{
}

UIElement::UIElement(const nlohmann::json& prop):id()
{
	SetProperties(prop);
}


void UIElement::SetProperties(const nlohmann::json& item)
{
	if (item.contains("id")) {
		id = item["id"];

	}
	// Empty implementation or minimal default implementation
}

void UIElement::Update(sf::RenderWindow& window)
{

}

void UIElement::HandleEvents(const sf::Event& e, sf::RenderWindow& window)
{
}
