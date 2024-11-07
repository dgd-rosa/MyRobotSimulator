#include "Game.hpp"
#include "menu/menu.hpp"

#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

enum GameState
{
    MENU,
    GAME
};

class GameManager
{
    private:
        //Window
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;

        void initWindow();


    public:
        std::unique_ptr<Game> game;
        std::unique_ptr<Menu> menu;
        GameState state;

        GamePanelInfo* gamePanelInfo;

        GameManager();

        //Accessors
        const bool running() const;

        //Functions
        void pollEvents();


        void update();
        void render();
};

#endif