#include <SFML/Graphics.hpp>
#include "exceptions/GameException.hpp"

#ifndef SUPEROBJECT_HPP
#define SUPEROBJECT_HPP

enum ObjectType
{
    POWER_UP,
    POINTS
};

enum PowerUpType
{
    BATTERY_BOOST,
    LAST
};

class SuperObject
{
    public:
        virtual ~SuperObject() = default;

        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f pos;
        sf::FloatRect bounds;

        ObjectType type;
        bool collision = false;

        const sf::FloatRect getBounds() const;
        const sf::Vector2f & getPos() const;
        
        void setPosition(sf::Vector2f pos);
        void render(sf::RenderTarget* target);

};

class PowerUpObject : public SuperObject
{
    public:
        PowerUpType powerUp_type;
        PowerUpObject(){
            this->type = POWER_UP;
        }
        virtual ~PowerUpObject() = default;
};

class PointObject : public SuperObject
{
    public:
        unsigned int points = 0;
        PointObject(){
            this->type = POINTS;
        }
        virtual ~PointObject() = default;
};

#endif