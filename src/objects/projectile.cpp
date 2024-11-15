#include "objects/projectile.hpp"

Projectile::Projectile()
{
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

    this->movement_speed = 1.f;
}

Projectile::Projectile(sf::Texture texture, Direction direction, float start_x, float start_y, float movement_speed, unsigned int damage)
{
    this->texture = texture;

    this->pos = sf::Vector2f(start_x, start_y);

    this->sprite.setPosition(sf::Vector2f(start_x, start_y));
    this->sprite.setTexture(this->texture);
    this->sprite.scale(1.5,1.5);
    this->bounds = this->sprite.getGlobalBounds();

    this->movement_speed = movement_speed;
    this->direction = direction;
    this->damage = damage;
}

const sf::FloatRect Projectile::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const sf::Vector2f & Projectile::getPos() const
{
    return this->sprite.getPosition();
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
    
}

void Projectile::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}