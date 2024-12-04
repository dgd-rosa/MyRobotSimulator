#include <SFML/Graphics.hpp>
#include "exceptions/GameException.hpp"
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

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

        std::string texture_path;
        std::string texture2_path;
        std::string texture3_path;
        sf::Texture texture;
        sf::Texture texture2;
        sf::Texture texture3;
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