#include "objects/OBJ_Screw.hpp"


OBJ_Screw::OBJ_Screw()
{
    if(!this->texture.loadFromFile("images/objects/screw.png"))
    {
        throw GameException("Could not load Screw Texture");
    }
    
    this->texture.setSmooth(false);

    this->pos = sf::Vector2f(500.f, 200.f);
    this->sprite.setPosition(this->pos);
    this->sprite.setTexture(this->texture);
    this->sprite.scale(1.5,1.5);
    this->bounds = this->sprite.getGlobalBounds();

    this->points = 10;
}


