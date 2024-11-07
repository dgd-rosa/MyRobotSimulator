#include <SFML/Graphics.hpp>
#include <iostream>
#include "tiles/gameTile.hpp"
#include "entities/entity.hpp"
#include "CollisionChecker.hpp"
#include "entities/battery.hpp"

#ifndef ROBOT_HPP
#define ROBOT_HPP

using namespace std;


class Robot : public Entity{
    private:
        unsigned int points = 0;
        unsigned int point_multiplier = 1;
        Battery* battery;
        

        void initShape();
        void initVariables();
        

    public:
        Robot(float start_x=0.f, float start_y=0.f);
        virtual ~Robot();

        //Accessor
        const sf::Vector2f& getPos() const;
        unsigned int getPoints();

        //Modifiers
        

        // Functions
        void updateInput();
        void updateMovement();
        bool obstacleCollision(sf::Sprite obstacle);
        void moveAfterCollision(sf::FloatRect myBounds, sf::FloatRect obstacleBounds, bool isDamaged);
        void checkObstacles(CollisionChecker* collisionChecker);
        void pickUpObject(int idx, std::vector<SuperObject*>& objs);
        void pickUpPowerUp(PowerUpObject* obj);
        void pickUpPoint(PointObject* obj);
        
        

        void update(CollisionChecker* collisionChecker);
        void render(sf::RenderTarget* target);
};

#endif