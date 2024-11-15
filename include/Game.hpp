#include <vector>
#include <ctime>
#include "tiles/tileManager.hpp"
#include "CollisionChecker.hpp"
#include "objects/object_spawner.hpp"
#include "header/header.hpp"
#include "menu/menu.hpp"
#include <iostream>

/*
    Class that acts as the game engine
    Wrapper Class
 */

#ifndef GAME_HPP
#define GAME_HPP


class Game
{
    private:
        //Game objects
        Robot robot;
        TileManager* tileManager;
        std::vector<Enemy*> enemyList;
        std::vector<Projectile*> enemyProjectiles;
        std::vector<Projectile*> robotProjectiles;

        CollisionChecker* collisionChecker;
        ObjectSpawner* objectSpawner;
        std::unique_ptr<ProjectileManager> projectileManager;
        std::unique_ptr<EnemyManager> enemyManager;

        //World
        sf::Texture worldBackgroundText;
        sf::RectangleShape worldBackground;
        std::unique_ptr<Header> header;
        Mode mode = INGAME;

        //Pause Mode
        sf::RectangleShape pauseBackground;
        sf::Font font;
        sf::Text pauseText;


        //Mouse positions
        sf::Vector2i mousePosWindow;


        void initVariables(GamePanelInfo* gpInfo);
        void initRobot();
        void initPauseText();

    public:
        GamePanelInfo* gamePanelInfo;


        Game(GamePanelInfo* gpInfo);
        virtual ~Game();
        
        void checkGameOver();
        void pauseGame();
        void resumeGame();
        void handleEnterPressed();
        
        void shootProjectiles();
        void updateCollisions();
        void updateWindowCollision();
        void update();


        void render(sf::RenderTarget* target);
};


#endif