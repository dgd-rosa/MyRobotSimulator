#include "entities/robot.hpp"

#ifndef ENEMY_HPP
#define ENEMY_HPP

class Enemy : public Entity 
{
    private:
        Direction facing_direction = RIGHT;

        //Shot
        float light_attack_speed;
        int light_attack_damage;
        chrono::milliseconds light_attack_cooldown;
        chrono::time_point<chrono::steady_clock> lastTimeShot = chrono::steady_clock::now();
        bool firstShot = true;

        chrono::milliseconds time_to_wait_before_shooting = std::chrono::milliseconds(1000);
        chrono::time_point<chrono::steady_clock> time_robot_in_sight = chrono::steady_clock::now();
        bool startedToWait = false;


        std::string right1TexturePath;
        std::string right2TexturePath;
        std::string left1TexturePath;
        std::string left2TexturePath;

        sf::Texture lightAttackTexture;
        sf::Texture lightAttackTextureUp;
        sf::Texture lightAttackTextureDown;
        sf::Texture lightAttackTextureLeft;
        sf::Texture lightAttackTextureRight;

        std::string lightAttackUpPath;
        std::string lightAttackDownPath;
        std::string lightAttackLeftPath;
        std::string lightAttackRightPath;

        void initShape();
        void initConfigFile();
        void initAttackTexture();

    public:
        Enemy(float start_x, float start_y, std::weak_ptr<SoundManager> soundManager);
        ~Enemy() = default;


        void updateMovement(Robot* robot);
        void moveEnemy();

        Projectile* shootToRobot(Robot* robot);
        Projectile* createProjectileToShoot();
        void hitByProjectile(Projectile* projectile) override;
        void dyingAnimation() override;


        //Bollean
        bool isDead();
        bool isFacingRobot(Robot* robot);
        
        
        void update(Robot* robot);
        void render(sf::RenderTarget* target);

};

#endif