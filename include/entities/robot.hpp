#include <iostream>
#include "tiles/gameTile.hpp"
#include "entities/entity.hpp"
#include "entities/battery.hpp"

#ifndef ROBOT_HPP
#define ROBOT_HPP

using namespace std;


class Robot : public Entity{
    private:
        unsigned int points = 0;
        unsigned int point_multiplier = 1;
        Battery* battery;

        sf::Texture lightAttackTextureUp;
        sf::Texture lightAttackTextureDown;
        sf::Texture lightAttackTextureLeft;
        sf::Texture lightAttackTextureRight;

        //Shooting Variables
        chrono::milliseconds shoot_cooldown = std::chrono::milliseconds(3000);
        chrono::time_point<chrono::steady_clock> lastTimeShot = chrono::steady_clock::now();
        bool firstShot = true;

        void initShape();
        void initVariables();
        void initAttackTexture();
        

    public:
        Robot(float start_x=0.f, float start_y=0.f);
        virtual ~Robot();

        //Accessor
        unsigned int getPoints();
        unsigned int getBatteryValue();
        unsigned int getLifePoints();

        //Modifiers
        

        // Functions
        void updateInput();
        void updateMovement();
        Projectile* shoot();
        
        //bool obstacleCollision(sf::Sprite obstacle);
        void obstacleCollision() override;
        
        void moveAfterCollision(sf::FloatRect myBounds, sf::FloatRect obstacleBounds, bool isDamaged);
        
        void pickUpObject(SuperObject* obj) override;
        void pickUpPowerUp(PowerUpObject* obj);
        void pickUpPoint(PointObject* obj);
        void hitByProjectile(Projectile* projectile) override;
        
        //attacks
        Projectile* lightAttack();

        void update();
        void render(sf::RenderTarget* target);
};

#endif