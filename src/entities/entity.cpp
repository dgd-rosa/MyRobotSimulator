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

void Entity::setDirectionVelocity(Direction direction, float vel)
{
    this->direction = direction;
    switch (this->direction)
    {
    case LEFT:
        this->setVelocity(-vel, 0.f);
        break;
    case RIGHT:
        this->setVelocity(vel, 0.f);
        break;
    case UP:
        this->setVelocity(0.f, -vel);
        break;
    case DOWN:
        this->setVelocity(0.f, vel);
        break;
    default:
        break;
    }
}

/**
 *      Method for Obstacle Collision -> Set velocity to zero
 */
void Entity::obstacleCollision()
{
    this->setVelocity(0.f, 0.f);
}


/**
 *   Method to check if Sound Manager pointer is still pointing to an object
 * 
 */

void Entity::soundEffect(std::string string)
{
    if(auto real_sound_manager = this->soundManager.lock())
    {
        real_sound_manager->playSound(string);
    }
}

void Entity::damagedAnimation()
{
    this->damagedCounter++;

    sf::Color currentColor = this->realColor;

    int i = 10;
    
    if(damagedCounter > 0 && damagedCounter <= i)
    {
        // Increase the red component, decrease green and blue for a red tint
        currentColor.r = 255;
        currentColor.g = std::max(realColor.g - 100, 0);   // Reduce green but not below 0
        currentColor.b = std::max(realColor.b - 100, 0);   // Reduce blue but not below 0
    }
    else if(damagedCounter > i && damagedCounter <= 2*i)
    {
        // Increase the red component, decrease green and blue for a red tint
        currentColor.r = 200; // Add red but cap at 255
        currentColor.g = std::max(realColor.g - 100, 0);   // Reduce green but not below 0
        currentColor.b = std::max(realColor.b - 100, 0);   // Reduce blue but not below 0
    }
    else if(damagedCounter > 2*i && damagedCounter <= 3*i)
    {
        // Increase the red component, decrease green and blue for a red tint
        currentColor.r = 255; // Add red but cap at 255
        currentColor.g = std::max(realColor.g - 100, 0);   // Reduce green but not below 0
        currentColor.b = std::max(realColor.b - 100, 0);   // Reduce blue but not below 0
    }
    else if(damagedCounter > 3*i && damagedCounter <= 4*i)
    {
        // Increase the red component, decrease green and blue for a red tint
        currentColor.r = 200; // Add red but cap at 255
        currentColor.g = std::max(realColor.g - 100, 0);   // Reduce green but not below 0
        currentColor.b = std::max(realColor.b - 100, 0);   // Reduce blue but not below 0
    }
    else if(damagedCounter > 4*i && damagedCounter <= 5*i)
    {
        // Increase the red component, decrease green and blue for a red tint
        currentColor.r = 255; // Add red but cap at 255
        currentColor.g = std::max(realColor.g - 100, 0);   // Reduce green but not below 0
        currentColor.b = std::max(realColor.b - 100, 0);   // Reduce blue but not below 0
    }
    else if(damagedCounter > 5*i && damagedCounter <= 6*i)
    {
        // Increase the red component, decrease green and blue for a red tint
        currentColor.r = 200; // Add red but cap at 255
        currentColor.g = std::max(realColor.g - 100, 0);   // Reduce green but not below 0
        currentColor.b = std::max(realColor.b - 100, 0);   // Reduce blue but not below 0
    }
    else{
        this->damagedCounter = 0;
        this->isDamaged = false;
    }

    this->sprite.setColor(currentColor);
}