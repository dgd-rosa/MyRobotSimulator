#include "objects/OBJ_BatteryBoost.hpp"

OBJ_BatteryBoost::OBJ_BatteryBoost()
{
    if(!this->texture.loadFromFile("images/objects/battery_boost.png"))
    {
        throw GameException("Could not load Battery Boost Texture");
    }
    
    this->texture.setSmooth(false);

    this->powerUp_type = BATTERY_BOOST;

    this->pos = sf::Vector2f(500.f, 200.f);
    this->sprite.setPosition(this->pos);
    this->sprite.setTexture(this->texture);
    this->sprite.scale(1.5,1.5);
    this->bounds = this->sprite.getGlobalBounds();
}