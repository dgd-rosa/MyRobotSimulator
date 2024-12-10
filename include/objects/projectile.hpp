#include <SFML/Graphics.hpp>
#include "super_object.hpp"
#include "enum.hpp"

#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP



class Projectile : public SuperObject
{
    public:
        sf::Texture texture;
        sf::Sprite sprite;

        //Collision Rectangle
        sf::RectangleShape collisionRect;
        int left_rect, top_rect, width_rect, height_rect = 0;

        Direction direction;
        float movement_speed;
        unsigned int damage;

        Projectile();
        Projectile(sf::Texture texture, Direction direction, float start_x, float start_y, float movement_speed, unsigned int damage);
        virtual ~Projectile() = default;


        const sf::FloatRect getBounds() const;
        const sf::FloatRect getCollisionBounds() const;
        const sf::Vector2f & getPos() const;
        Direction getDirection();

        
        void update();
        void render(sf::RenderTarget* target);
};

#endif