#include <SFML/Graphics.hpp>
#include "objects/super_object.hpp"
#include "objects/projectile.hpp"
#include <iostream>
#include "enum.hpp"
#include "sound/sound.hpp"

#ifndef ENTITY_HPP
#define ENTITY_HPP


class Entity
{
    protected:
        std::weak_ptr<SoundManager> soundManager;

        sf::Vector2f velocity;
        float movementSpeed;
        Direction direction;
        unsigned int life_points;

        //counter
        unsigned int spriteCounter;
        unsigned int spriteNumber;
        int dyingCounter;

        

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


        //counter


    public:
        //state
        bool attacking = false;
        bool alive = true;
        bool dying = false;

        //Constructor
        Entity();
        virtual ~Entity() = default;

        //Gets
        const sf::FloatRect getBounds() const;
        const sf::FloatRect getCollisionBounds() const;
        sf::Vector2f getVelocity();
        const sf::Vector2f& getPos() const;
        const Direction getDirection() const;
        unsigned int getLifePoints(){return this->life_points;}

        //Sets
        void setPosition(sf::Vector2f pos);
        void setPosition(float x, float y);
        void setVelocity(const float velocity_x, const float velocity_y);

        virtual void update(){};
        virtual void obstacleCollision();
        virtual void pickUpObject(SuperObject* object){};
        virtual void hitByProjectile(Projectile* projectile){};
        virtual void hitEntity(Entity* entity){};
        virtual void dyingAnimation(){};
};


#endif