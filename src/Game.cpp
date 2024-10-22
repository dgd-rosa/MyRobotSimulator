#include "Game.hpp"


// Private Functions

void Game::initVariables(){
    this->window = nullptr;

}

void Game::initWindow(){
    this->videoMode.width = 800;
    this->videoMode.height = 600;
    this->window = new sf::RenderWindow(this->videoMode, "Robot 2D Simulator", sf::Style::Titlebar | sf::Style::Close);
    

    this->window->setFramerateLimit(60);
}

void Game::initRobot(){

    
}

void Game::initWorld()
{
    if(!this->worldBackgroundText.loadFromFile("images/2d_floor.jpg")){
        std::cout << "Error::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
        return;       
    }

    this->worldBackground.setSize(sf::Vector2f(this->videoMode.width, this->videoMode.height));
    this->worldBackground.setOutlineThickness(1);
    this->worldBackground.setTexture(&this->worldBackgroundText, false);

}



Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initRobot();
    this->initWorld();
}

Game::~Game()
{
    delete this->window;    
}


//Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}



//Functions
void Game::pollEvents()
{
    while(this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Game::updateCollision()
{
    //Left Bound
    if(this->robot.getBounds().left < 0.f)
    {
        this->robot.setPosition(0.f, this->robot.getBounds().top);
    }
    
    //Right bound
    else if(this->robot.getBounds().left + this->robot.getBounds().width > this->videoMode.width )
    {
        this->robot.setPosition(this->videoMode.width - this->robot.getBounds().width, this->robot.getBounds().top);
    }
    
    //Top Bound
    if(this->robot.getBounds().top < 0.f)
    {
        this->robot.setPosition(this->robot.getBounds().left, 0.f);
    }
    //Bottom Bound
    else if(this->robot.getBounds().top + this->robot.getBounds().height > this->videoMode.height)
    {
        this->robot.setPosition(this->robot.getBounds().left, this->videoMode.height - this->robot.getBounds().height);
    }
}

void Game::update(){
    
    this->pollEvents();

    this->robot.update(this->window);

    this->updateCollision();
}

void Game::renderWorld(){

    this->window->draw(this->worldBackground);
}

void Game::render(){

    /*
        Renders the game objects
        -clear old frame
        -render objects
        -dispay frame in window
    */

    this->window->clear(sf::Color(255, 0, 0, 255));

    //Draw Background
    this->renderWorld();

    //Draw Game

    this->robot.render(this->window);



    this->window->display();
}



