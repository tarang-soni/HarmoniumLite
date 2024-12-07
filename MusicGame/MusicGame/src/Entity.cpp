#include "Entity.h"

Entity::Entity()
	:entities()
{
}

void Entity::PollEvents(const sf::Event& e)
{
	for (auto& entity : entities)
	{
		entity->PollEvents(e); // Propagate event polling to child entities
	}
}

void Entity::Update()
{
	for (auto& entity : entities)
	{
		entity->Update();
	}
}

void Entity::Render(sf::RenderTarget& target)const
{
	for (auto& entity : entities)
	{
		entity->Render(target);
	}
}
