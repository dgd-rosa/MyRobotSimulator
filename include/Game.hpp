#include <vector>
#include <ctime>
#include "entities/robot.hpp"
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

enum Mode
{
    INGAME,
    PAUSE
};

class Game
{
    private:
        //Game objects
        Robot robot;
        TileManager* tileManager;

        CollisionChecker* collisionChecker;
        ObjectSpawner* objectSpawner;

        //World
        sf::Texture worldBackgroundText;
        sf::RectangleShape worldBackground;
        std::unique_ptr<Header> header;
        Mode mode = INGAME;


        //Mouse positions
        sf::Vector2i mousePosWindow;


        void initVariables(GamePanelInfo* gpInfo);
        void initRobot();

    public:
        GamePanelInfo* gamePanelInfo;


        Game(GamePanelInfo* gpInfo);
        virtual ~Game();
        
        void update();
        void updateWindowCollision();

        void render(sf::RenderTarget* target);
};


#endif