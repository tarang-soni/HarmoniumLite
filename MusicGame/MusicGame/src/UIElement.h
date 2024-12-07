#pragma once
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "UIProperties.h"
#include "Core.h"
#include <string>
class UIElement:public sf::Drawable,public sf::Transformable
{

	// Inherited via Drawable
public:
	UIElement();
	UIElement(const nlohmann::json& prop);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
	virtual void SetProperties(const  nlohmann::json& item );
	virtual void Update(sf::RenderWindow& window);
	virtual void HandleEvents(const sf::Event& e, sf::RenderWindow& window);

	std::string id;

};

