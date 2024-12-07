#pragma once
#include "Entity.h"
class GameObject :
    public Entity,public sf::Drawable,public sf::Transformable
{
public:
    GameObject();
    GameObject(float x, float y);
    GameObject(sf::Vector2f pos);
    
    virtual void PollEvents(const sf::Event& e) override;
    virtual void Update() override;
    virtual void Render(sf::RenderTarget& target)const override;

    // Inherited via Drawable
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
