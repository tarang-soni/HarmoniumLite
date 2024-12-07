#include "Button.h"
#include <SFML/Window/Mouse.hpp>
#include"Core.h"
Button::Button(const  nlohmann::json& prop) 
	:UIElement(prop) ,
	_txt(prop),
	_btn(),
	OnClick(),
	currentBtnState(States::Default)
{
	SetProperties(prop);

}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	target.draw(_btn);
	target.draw(_txt);
}

void Button::Update(sf::RenderWindow& window)
{
	_btn.setFillColor(stateColors[currentBtnState]);
}

void Button::HandleEvents(const sf::Event& e, sf::RenderWindow& window)
{
	switch (e.type)
	{
	case sf::Event::MouseMoved:

		if (IsHover(window))
		{

			currentBtnState = States::Hover;
		}
		else
		{
			currentBtnState = States::Default;
		}
		
		break;
	case sf::Event::MouseButtonPressed:
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (IsHover(window))
			{
				if (OnClick) {
					OnClick();
				}
				currentBtnState = States::Pressed;
			}
			else
			{
				currentBtnState = States::Default;
			}
		}
		break;
	case sf::Event::MouseButtonReleased:

		if (e.mouseButton.button == sf::Mouse::Left) 
		{
			if (IsHover(window))
			{
				currentBtnState = States::Hover; // Stay in Hover if still hovering
			}
			else
			{
				currentBtnState = States::Default;
			}
		}

		break;
	default:
		break;
	}
}

void Button::SetProperties(const nlohmann::json& prop)
{

	stateColors[States::Default] = hexToColor(prop["buttonStateColors"]["Default"]);   // Default state color
	stateColors[States::Hover] = hexToColor(prop["buttonStateColors"]["Hover"]);   // Hover state color
	stateColors[States::Pressed] = hexToColor(prop["buttonStateColors"]["Pressed"]);    // Pressed state color

	_btn.setSize(sf::Vector2f(prop["size"]["width"], prop["size"]["height"]));
	sf::FloatRect btnBounds = _btn.getLocalBounds();
	_btn.setOrigin(btnBounds.left + btnBounds.width / 2, btnBounds.top + btnBounds.height / 2);

	_btn.setPosition(prop["position"]["x"], prop["position"]["y"]);
	_btn.setFillColor(sf::Color::Cyan);
}

bool Button::IsHover(sf::RenderWindow& window)
{
	auto mpos = sf::Mouse::getPosition(window);
	sf::Vector2f mposf = sf::Vector2f(static_cast<float>(mpos.x), static_cast<float>(mpos.y));
	auto a = _btn.getGlobalBounds();
	if (_btn.getGlobalBounds().contains(mposf)) {
		return true;
	}
	return false;
}

void Button::SetOnClick(std::function<void()> onClick)
{
	OnClick = onClick;
}
