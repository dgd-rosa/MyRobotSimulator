#include <SFML/Graphics.hpp>

#ifndef ENTITY_HPP
#define ENTITY_HPP

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

class Entity
{
    public:
        sf::Vector2f velocity;
        int movementSpeed;
        Direction direction;

        unsigned int spriteCounter;
        unsigned int spriteNumber;

        //Texture
        sf::Texture right_texture1;
        sf::Texture right_texture2;
        sf::Texture left_texture2;
        sf::Texture left_texture1;
        sf::Texture up_texture1;
        sf::Texture up_texture2;
        sf::Texture down_texture1;
        sf::Texture down_texture2;
        sf::Sprite sprite;

        //Collision Rectangle
        sf::RectangleShape collisionRect;
        int left_rect, top_rect, width_rect, height_rect = 0;
        bool collisionOn = false;

        //Constructor
        Entity();    

        //Gets
        const sf::FloatRect getBounds() const;
        sf::Vector2f getVelocity();

        //Sets
        void setPosition(sf::Vector2f pos);
        void setPosition(float x, float y);
        void setVelocity(const float velocity_x, const float velocity_y);
};


#endif