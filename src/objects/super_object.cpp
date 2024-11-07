#include "objects/super_object.hpp"

void SuperObject::setPosition(sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
    this->bounds = this->sprite.getGlobalBounds();
}

void SuperObject::render(sf::RenderTarget* target)
{
    if(target == nullptr)
    {
        return;
    }

    target->draw(this->sprite);      
}
