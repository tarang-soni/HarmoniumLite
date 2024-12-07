#include "Text.h"
#include "UIFactory.h"
#include <nlohmann/json.hpp>
#include"Core.h"

Text::Text()
	:UIElement(),
	_font(),
	_txt(),
	_fontSize()
{
}

Text::Text(const  nlohmann::json& prop) :UIElement(prop),
_font(),
_txt(),
_fontSize()
{
	SetProperties(prop);
}
void Text::SetProperties(const nlohmann::json& props)
{
	UIElement::SetProperties(props);
	_font = sf::Font();
	std::string fontFamily = props["fontFamily"];
	if (!_font.loadFromFile(fontFamily + ".ttf"))
	{
		throw std::runtime_error("Wrong file");
	}
	if (props.contains("content")) {
		std::string content = props["content"];
		_txt.setString(content);
	}
	if (props.contains("textColor")) {
		std::string color = props["textColor"];
		_txt.setFillColor(hexToColor(color));
	}
	_txt.setFont(_font);
	if (props.contains("fontSize")) {
		int fontSize = props["fontSize"].get<int>();
		_txt.setCharacterSize(fontSize);
	}
	if (props.contains("position")) 
	{
		sf::FloatRect textBounds = _txt.getLocalBounds();
		_txt.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);


		_txt.setPosition(props["position"]["x"], props["position"]["y"]);
	}


	

}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_txt);
}
