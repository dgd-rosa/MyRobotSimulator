#include "Game.hpp"
#include "scoreboard.hpp"
#include "menu/menu.hpp"
#include "sound/sound.hpp"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

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
        std::shared_ptr<SoundManager> soundManager;
        std::unique_ptr<Scoreboard> scoreBoard;
        GameState state;

        GamePanelInfo* gamePanelInfo;


        GameManager();

        //Accessors
        const bool running() const;

        //Functions
        void pollEvents();
        void handleKeyPressedEvent(sf::Event &event);
        


        void update();
        void render();
};

#endif