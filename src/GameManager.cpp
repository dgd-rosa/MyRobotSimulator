#include "GameManager.hpp"


GameManager::GameManager()
{
    this->gamePanelInfo = new GamePanelInfo();

    this->soundManager = std::make_shared<SoundManager>();                         

    this->game = std::make_unique<Game>(this->gamePanelInfo, this->soundManager);

    this->menu = std::make_unique<Menu>(this->gamePanelInfo->screenWidth, this->gamePanelInfo->screenHeight, this->soundManager);

    this->state = MENU;

    this->window = nullptr;

    this->initWindow();
}

void GameManager::initWindow()
{
    this->videoMode.width = this->gamePanelInfo->screenWidth;
    this->videoMode.height = this->gamePanelInfo->screenHeight;
    this->window = new sf::RenderWindow(this->videoMode, "Robot 2D Simulator", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

//Accessors
const bool GameManager::running() const
{
    return this->window->isOpen();
}

void GameManager::handleKeyPressedEvent(sf::Event &event)
{
    if(this->event.type == sf::Event::KeyPressed)
    {
        if(this->event.key.code == sf::Keyboard::Escape)
        {
            if(this->state == GAME)
            {
                this->state = MENU;
                this->menu = std::make_unique<Menu>(this->gamePanelInfo->screenWidth, this->gamePanelInfo->screenHeight, this->soundManager);
                this->soundManager->stopMusic();
            }
        }
        else if(this->state == MENU)
        {
            if(this->menu->isEnterPressed())
            {
                this->soundManager->playSound("menu_click");
                if(this->menu->menuOption == START_GAME)
                {
                    this->state = GAME;
                    this->game = std::make_unique<Game>(this->gamePanelInfo, this->soundManager);
                    this->window->setSize(sf::Vector2u(this->gamePanelInfo->screenWidth, this->gamePanelInfo->screenHeight));
                    this->soundManager->playMusic();
                }
                else if(this->menu->menuOption == EXIT)
                    this->window->close();
                else if(this->menu->menuOption == SCOREBOARD)
                {
                    this->menu->currentMenuState = SCOREBOARD_MENU;
                }
            }
        }
        else if(this->event.key.code == sf::Keyboard::Enter)
        {
            if(this->state == GAME)
            {
                this->game->handleEnterPressed();   
            }
            if(this->game->getGameMode() == GAME_OVER)
            {
                this->state = MENU;
                this->menu->scoreboard->saveScore((this->game->getScore()));
                this->soundManager->stopMusic();
            }
        }    
    }
}

//Functions
void GameManager::pollEvents()
{
    while(this->window->pollEvent(this->event))
    {
        if(this->event.type == sf::Event::Closed)
        {
            this->window->close();
        }
        
        this->handleKeyPressedEvent(event);

        if(this->state == GAME)
        {
            this->game->handleKeyPressedEvent(event);
        }
        else if(this->state == MENU)
        {
            this->menu->handleKeyPressedEvents(event);
        }
        
    }
}

void GameManager::update()
{
    this->pollEvents();
    
    if(this->state == GAME)
    {
        this->game->update(this->event);
    }
}

void GameManager::render()
{
    /*
        Renders the menu or the game
        - clears window
        -render either menu or game
        -display
    */

    this->window->clear(sf::Color(0, 0, 0, 255));

    if(this->state == MENU)
    {
        this->menu->render(this->window);
    }
    else if(this->state == GAME)
    {
        this->game->render(this->window);
    }


    this->window->display();
}