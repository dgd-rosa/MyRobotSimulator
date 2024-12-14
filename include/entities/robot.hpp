#include <iostream>
#include "tiles/gameTile.hpp"
#include "entities/entity.hpp"
#include "objects/OBJ_Heart.hpp"
#include "entities/battery.hpp"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

#ifndef ROBOT_HPP
#define ROBOT_HPP


class Robot : public Entity{
    private:
        unsigned int points;
        unsigned int point_multiplier;
        unsigned int level;
        unsigned int current_xp = 0;
        unsigned int xp_for_next_level;
        unsigned int xp_multiplier;

        int levelUpCounter = 0;
        bool isLevelingUp = false;

        Direction face_direction = RIGHT;
        Battery* battery;

        sf::Texture lightAttackTextureUp;
        sf::Texture lightAttackTextureDown;
        sf::Texture lightAttackTextureLeft;
        sf::Texture lightAttackTextureRight;
        std::string lightAttackUpPath;
        std::string lightAttackDownPath;
        std::string lightAttackLeftPath;
        std::string lightAttackRightPath;


        std::string right1TexturePath;
        std::string right2TexturePath;
        std::string left1TexturePath;
        std::string left2TexturePath;
        std::string up1TexturePath;
        std::string up2TexturePath;
        std::string down1TexturePath;
        std::string down2TexturePath;


        //Shooting Variables
        chrono::milliseconds light_attack_cooldown;
        chrono::time_point<chrono::steady_clock> lastTimeShot = chrono::steady_clock::now();
        float light_attack_speed;
        int light_attack_damage;
        bool firstShot = true;

        void initShape();
        void initVariables();
        void initConfigFile();
        void initAttackTexture();

        void updateXP();
        void levelUp();

        void pickUpPowerUp(PowerUpObject* obj);
        void pickUpPoint(PointObject* obj);
        void pickUpLifeBoost(PowerUpObject* obj);

    public:
        Robot(float start_x, float start_y, std::shared_ptr<SoundManager> soundManager);
        virtual ~Robot();

        //Accessor
        unsigned int getPoints();
        unsigned int getBatteryValue();
        unsigned int getLifePoints();
        unsigned int getLevel();
        unsigned int getPointsToNextLvl();
        int getLightAttackDamage();
        float getLightAttackCooldown();
        float getLightAttackSpeed();
        float getMovementSpeed();
        bool getIsLevelingUp();
        void setIsLevelingUp(bool);

        //handlers
        void handlingKeyPressedEvent(sf::Event &event);


        // Functions
        void updateInput();
        void updateMovement();
        Projectile* shoot();
        void increasePoints(int val);
        
        
        void obstacleCollision() override;
        void moveAfterCollision(Entity* entity);
        
        void pickUpObject(SuperObject* obj) override;
        void hitByProjectile(Projectile* projectile) override;
        void hitEntity(Entity* entity) override;
        
        //attacks
        Projectile* lightAttack();

        void update();
        void render(sf::RenderTarget* target);
};

#endif