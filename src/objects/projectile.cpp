#include "objects/projectile.hpp"

Projectile::Projectile()
{
    this->movement_speed = 1.f;

    if(!this->texture.loadFromFile("images/bullets/red_bullet.png"))
    {
        throw GameException("Could not load Red Projectile Texture");
    }

    std::cout << "Projectile: No arguments Constructor" << std::endl;
    
    this->texture.setSmooth(false);

    this->pos = sf::Vector2f(500.f, 200.f);
    this->sprite.setPosition(this->pos);
    this->sprite.setTexture(this->texture);
    this->sprite.scale(1.5,1.5);
    this->bounds = this->sprite.getGlobalBounds();


    //Setup Collision Rectangle
    sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();

    
    this->collisionRect.setSize(sf::Vector2f(spriteBounds.width-20, spriteBounds.height-20));
    sf::FloatRect rectBounds = this->collisionRect.getGlobalBounds();
    //Set Origin to the rectangle Center
    this->collisionRect.setOrigin(rectBounds.width/2, rectBounds.height/2);
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+spriteBounds.width/2, spriteBounds.top+spriteBounds.height/2));
    this->collisionRect.setFillColor(sf::Color::Red);
}

Projectile::Projectile(sf::Texture texture, Direction direction, float start_x, float start_y, float movement_speed, unsigned int damage)
{
    this->movement_speed = movement_speed;
    this->direction = direction;
    this->damage = damage;
    this->pos = sf::Vector2f(start_x, start_y);

    this->texture = texture;

    this->sprite.setPosition(sf::Vector2f(start_x, start_y));
    this->sprite.setTexture(this->texture);
    this->sprite.scale(1.5,1.5);
    this->bounds = this->sprite.getGlobalBounds();

    
    //Setup Collision Rectangle
    sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();

    
    this->collisionRect.setSize(sf::Vector2f(spriteBounds.width-25, spriteBounds.height-25));
    sf::FloatRect rectBounds = this->collisionRect.getGlobalBounds();
    //Set Origin to the rectangle Center
    this->collisionRect.setOrigin(rectBounds.width/2, rectBounds.height/2);
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+spriteBounds.width/2, spriteBounds.top+spriteBounds.height/2));
    this->collisionRect.setFillColor(sf::Color::Red);
}

const sf::FloatRect Projectile::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const sf::FloatRect Projectile::getCollisionBounds() const
{
    return this->collisionRect.getGlobalBounds();
}

const sf::Vector2f & Projectile::getPos() const
{
    return this->sprite.getPosition();
}

Direction Projectile::getDirection()
{
    return this->direction;
}

void Projectile::update()
{
    switch(this->direction)
    {
        case LEFT:
            this->sprite.move(sf::Vector2f(-this->movement_speed, 0));
            break;
        case RIGHT:
            this->sprite.move(sf::Vector2f(this->movement_speed, 0));
            break;
        case DOWN:
            this->sprite.move(sf::Vector2f(0, this->movement_speed));
            break;
        case UP:
            this->sprite.move(sf::Vector2f(0, -this->movement_speed));
            break;
    }
    
     //Update CollisionRect
    sf::FloatRect spriteBounds = this->getBounds();
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+spriteBounds.width/2, spriteBounds.top+spriteBounds.height/2));
}

void Projectile::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}