#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include "robot.hpp"

/*
    Class that acts as the game engine
    Wrapper Class
 */

#ifndef GAME_HPP
#define GAME_HPP

class Game
{
    private:
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;

        //Game objects
        Robot robot;

        //World
        sf::Texture worldBackgroundText;
        sf::RectangleShape worldBackground;

        //Mouse positions
        sf::Vector2i mousePosWindow;


        void initVariables();
        void initWindow();
        void initRobot();
        void initWorld();



    public:
        Game();
        virtual ~Game();

        //Accessors
        const bool running() const;

        //Functions
        void pollEvents();
        
        void update();
        void updateCollision();
        
        void render();
        void renderWorld();
};


#endif