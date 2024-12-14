#include <vector>
#include <ctime>
#include "tiles/tileManager.hpp"
#include "CollisionChecker.hpp"
#include "objects/object_spawner.hpp"
#include "header/header.hpp"
#include "menu/menu.hpp"
#include "menu/UI.hpp"
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
        std::vector<Projectile*> enemyProjectiles;
        std::vector<Projectile*> robotProjectiles;

        CollisionChecker* collisionChecker;
        ObjectSpawner* objectSpawner;
        std::unique_ptr<ProjectileManager> projectileManager;
        std::unique_ptr<EnemyManager> enemyManager;
        std::shared_ptr<SoundManager> soundManager;

        //World
        sf::Texture worldBackgroundText;
        sf::RectangleShape worldBackground;
        std::unique_ptr<Header> header;
        Mode mode = INGAME;

        //Pause Mode
        sf::RectangleShape pauseBackground;
        std::string fontPath;
        sf::Font font;
        sf::Text pauseText;
        sf::Text gameOverText;

        //LevelUP UI
        std::unique_ptr<LevelUpUI> levelUpUI;

        //score
        chrono::time_point<chrono::steady_clock> initTime;
        chrono::time_point<chrono::steady_clock> finishTime;

        //Mouse positions
        sf::Vector2i mousePosWindow;

        void initVariables(GamePanelInfo* gpInfo, std::shared_ptr<SoundManager>);
        void initRobot();
        void initText();
        void initConfig();

    public:
        GamePanelInfo* gamePanelInfo;

        Game(GamePanelInfo* gpInfo, std::shared_ptr<SoundManager>);
        virtual ~Game();
        
        void checkGameOver();
        void pauseGame();
        void resumeGame();
        void handleEnterPressed();
        Mode getGameMode() {return mode;}
        Score getScore();
        void shootProjectiles();

        void handleKeyPressedEvent(sf::Event& event);
        void updateCollisions();
        void updateWindowCollision();
        void update(sf::Event &event);


        void render(sf::RenderTarget* target);
};


#endif