#include "MusicKey.h"
#include <fstream>
#include <nlohmann/json.hpp>
bool MusicKey::_isMousePressed = false;
#define TXT _txt.GetText()
MusicKey::MusicKey(KeyType keyType, sf::Keyboard::Key key, Scales scale, std::string keyName,sf::Vector2f pos, sf::Vector2f size,KeyContext context)
	:GameObject(pos),
	_keyType(keyType),
	_rect(),
	_size(size),
	_context(context),
	_keyboardKey(key),
	_scale(scale),
	_defaultColor(keyType == KeyType::Major?sf::Color::White:sf::Color::Black),
	_pressedColor(sf::Color::Red),
	_keyPressType(None),
	_txt(),
	_keyName(keyName)
{
	CreateRect();
	
}

void MusicKey::PollEvents(const sf::Event& e)
{
	GameObject::PollEvents(e);

	std::string str = _keyName + std::to_string(_context.currentOctaveRef);
		sf::FloatRect textBounds = TXT.getLocalBounds();
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		TXT.setString(str);
		TXT.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);

		TXT.setPosition(sf::Vector2f(_rect.getPosition().x + _rect.getGlobalBounds().width / 2, _rect.getPosition().y + _rect.getGlobalBounds().height - TXT.getGlobalBounds().height * 2));

		break;
	case sf::Event::KeyReleased:
		if (e.key.code == sf::Keyboard::Key::LShift) 
		{
			TXT.setString(str);
			sf::FloatRect textBounds = TXT.getLocalBounds();
			TXT.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);

			TXT.setPosition(sf::Vector2f(_rect.getPosition().x + _rect.getGlobalBounds().width / 2, _rect.getPosition().y + _rect.getGlobalBounds().height - TXT.getGlobalBounds().height * 2));

		}
		break;

	case sf::Event::MouseButtonPressed:
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (IsHover()&&!_isMousePressed)
			{
				_isMousePressed = true;
				PlaySound(Mouse);
			}
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (e.mouseButton.button == sf::Mouse::Left)
		{

			_isMousePressed = false;
			if(_keyPressType == Mouse)
			StopSound();
			
		}
		break;
	}
}

void MusicKey::Update()
{
	GameObject::Update();
}

void MusicKey::Render(sf::RenderTarget& target) const
{
	GameObject::Render(target);
	target.draw(_rect);
	target.draw(_txt);
}

void MusicKey::PlaySound(KeyPressType keyPressType)
{
	_keyPressType = keyPressType;
	if (isPlaying) return;
	isPlaying = true;
	_rect.setFillColor(_pressedColor);
	_context.keysRef[_keyboardKey].setBuffer(_context.bufferRef[_context.currentOctaveRef][_scale]); \
		_context.keysRef[_keyboardKey].play();
}

void MusicKey::StopSound()
{
	_keyPressType = None;
	if (!isPlaying)return;
	isPlaying = false;
	_rect.setFillColor(_defaultColor);
	_context.keysRef[_keyboardKey].stop();
}


void MusicKey::CreateRect()
{	
	_rect.setSize(_size);
	_rect.setPosition(this->getPosition());
	_rect.setFillColor(_keyType == KeyType::Major? sf::Color::White : sf::Color::Black); 

	const char* path = "example.json";
	const char* screenType = "Game";
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error("Cannot open file: " + std::string(path));
	}
	nlohmann::json data = nlohmann::json::parse(file);

	_txt.SetProperties(data);
	std::string str = _keyName + std::to_string(_context.currentOctaveRef);
	TXT.setString(str);
	TXT.setFillColor(_keyType == KeyType::Major ? sf::Color::Black : sf::Color::White);
	sf::FloatRect textBounds = TXT.getLocalBounds();
	TXT.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);

	TXT.setPosition(sf::Vector2f(_rect.getPosition().x + _rect.getGlobalBounds().width / 2, _rect.getPosition().y + _rect.getGlobalBounds().height - TXT.getGlobalBounds().height * 2));

	
}

bool MusicKey::IsHover()
{
	auto mpos = sf::Mouse::getPosition(_context.windowRef);
	sf::Vector2f mposf = sf::Vector2f(static_cast<float>(mpos.x), static_cast<float>(mpos.y));
	auto a = _rect.getGlobalBounds();
	if (_rect.getGlobalBounds().contains(mposf)) {
		return true;
	}
	return false;
}
