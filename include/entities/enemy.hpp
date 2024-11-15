#include "entities/robot.hpp"

#ifndef ENEMY_HPP
#define ENEMY_HPP

class Enemy : public Entity 
{
    private:
        Direction facing_direction = RIGHT;

        //Shot
        chrono::milliseconds shoot_cooldown = std::chrono::milliseconds(3000);
        chrono::time_point<chrono::steady_clock> lastTimeShot = chrono::steady_clock::now();
        bool firstShot = true;

        chrono::milliseconds time_to_wait_before_shooting = std::chrono::milliseconds(1000);
        chrono::time_point<chrono::steady_clock> time_robot_in_sight = chrono::steady_clock::now();
        bool startedToWait = false;

        sf::Texture lightAttackTexture;
        sf::Texture lightAttackTextureUp;
        sf::Texture lightAttackTextureDown;
        sf::Texture lightAttackTextureLeft;
        sf::Texture lightAttackTextureRight;


        void initShape();
        void initAttackTexture();

    public:
        Enemy(float start_x=100.f, float start_y=243.f);
        ~Enemy() = default;


        void updateMovement(Robot* robot);

        Projectile* shootToRobot(Robot* robot);
        Projectile* createProjectileToShoot();
        void hitByProjectile(Projectile* projectile) override;


        //Bollean
        bool isDead();
        bool isFacingRobot(Robot* robot);
        
        
        void update(Robot* robot);
        void render(sf::RenderTarget* target);

};

#endif