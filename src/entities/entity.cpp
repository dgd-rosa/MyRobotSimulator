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

const sf::Vector2f & Entity::getPos() const
{
    return this->sprite.getPosition();
}

const Direction Entity::getDirection() const
{
    return this->direction;
}

const sf::FloatRect Entity::getCollisionBounds() const
{
    return this->collisionRect.getGlobalBounds();
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

/**
 *      Method for Obstacle Collision -> Set velocity to zero
 */
void Entity::obstacleCollision()
{
    std::cout << "Entity: Obstacle collision" << std::endl;
    this->setVelocity(0.f, 0.f);
}