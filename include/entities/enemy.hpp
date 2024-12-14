#include "entities/robot.hpp"
#include "menu/health_bar.hpp"

#ifndef ENEMY_HPP
#define ENEMY_HPP

enum EnemyType
{
    WEAK,
    MEDIUM,
    STRONG
};

class Enemy : public Entity 
{
    protected:
        EnemyType enemyType = WEAK;
        Direction facing_direction = RIGHT;
        unsigned int xp_points;
        chrono::milliseconds directionResetCooldown;
        chrono::time_point<chrono::steady_clock> lastTimeChangeDirections = chrono::steady_clock::now();

        //Shot
        float light_attack_speed;
        int light_attack_damage;
        chrono::milliseconds light_attack_cooldown;
        chrono::time_point<chrono::steady_clock> lastTimeShot = chrono::steady_clock::now();
        bool firstShot = true;

        chrono::milliseconds time_to_wait_before_shooting = std::chrono::milliseconds(2000);
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

        std::unique_ptr<HealthBar> healthBar;

        virtual void initShape();
        virtual void initConfigFile();
        void initAttackTexture();

    public:
        Enemy(){};
        Enemy(float start_x, float start_y, std::weak_ptr<SoundManager> soundManager);
        ~Enemy() = default;


        virtual void updateMovement(Robot* robot);
        void moveEnemy();

        Projectile* shootToRobot(Robot* robot);
        Projectile* createProjectileToShoot();
        void hitByProjectile(Projectile* projectile) override;
        void dyingAnimation() override;


        //Bollean
        bool isDead();
        bool isFacingRobot(Robot* robot);

        // Gets
        EnemyType getEnemyType();
        unsigned int getXPPoints(){return this->xp_points;}
        
        
        void update(Robot* robot);
        void render(sf::RenderTarget* target);
};

class EnemyWeak : public Enemy
{
    private:
        void initShape() override;
        void initConfigFile() override;

    public:
        EnemyWeak(float start_x, float start_y, std::weak_ptr<SoundManager> soundManager);
        ~EnemyWeak() = default;

        void updateMovement(Robot* robot) override;
};

class EnemyMedium : public Enemy
{
    private:
        void initShape() override;
        void initConfigFile() override;

    public:
        EnemyMedium(float start_x, float start_y, std::weak_ptr<SoundManager> soundManager);
        ~EnemyMedium() = default;

        void updateMovement(Robot* robot) override;
};

class EnemyStrong : public Enemy
{
    private:
        void initShape() override;
        void initConfigFile() override;
    
    public:
        EnemyStrong(float start_x, float start_y, std::weak_ptr<SoundManager> soundManager);
        ~EnemyStrong() = default;

        void updateMovement(Robot* robot) override;
};

#endif