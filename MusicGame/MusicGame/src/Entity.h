#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
class Entity :public sf::NonCopyable
{
public:
	Entity();
	virtual ~Entity() = default; // Virtual destructor for proper cleanup

	std::vector<std::unique_ptr<Entity>> entities;
	virtual void PollEvents(const sf::Event& e);
	virtual void Update();
	virtual void Render(sf::RenderTarget& target)const;
};