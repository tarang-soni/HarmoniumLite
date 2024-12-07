#include "GameObject.h"

GameObject::GameObject()
{
	setPosition(sf::Vector2f(0, 0));
}

GameObject::GameObject(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
}

GameObject::GameObject(sf::Vector2f pos)
{
	setPosition(pos);
}

void GameObject::PollEvents(const sf::Event& e)
{
	Entity::PollEvents(e);
}

void GameObject::Update()
{
	Entity::Update();
}

void GameObject::Render(sf::RenderTarget& target) const
{
	Entity::Render(target);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Render(target);
}
