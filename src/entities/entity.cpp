#include "entities/entity.hpp"

Entity::Entity()
{

}

const sf::FloatRect Entity::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

sf::Vector2f Entity::getVelocity()
{
    return this->velocity;
}

void Entity::setPosition(sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
    
    sf::FloatRect spriteBounds = this->getBounds();
    sf::FloatRect rectBounds = this->collisionRect.getLocalBounds();
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+this->left_rect, spriteBounds.top + spriteBounds.height - rectBounds.height));
}

void Entity::setPosition(float x, float y)
{
    this->sprite.setPosition(sf::Vector2f(x, y));

    sf::FloatRect spriteBounds = this->getBounds();
    sf::FloatRect rectBounds = this->collisionRect.getLocalBounds();
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+this->left_rect, spriteBounds.top + spriteBounds.height - rectBounds.height));
}

void Entity::setVelocity(const float velocity_x, const float velocity_y)
{
    this->velocity.x = velocity_x;
    this->velocity.y = velocity_y;
}