#include "objects/super_object.hpp"

const sf::FloatRect SuperObject::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const sf::Vector2f & SuperObject::getPos() const
{
    return this->sprite.getPosition();
}


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
