#include "Game.hpp"


// Private Functions

void Game::initVariables(GamePanelInfo* gpInfo){
    
    this->gamePanelInfo = gpInfo;

    this->tileManager = new TileManager(gamePanelInfo);

    this->objectSpawner = new ObjectSpawner();
    
    this->collisionChecker = new CollisionChecker(this->gamePanelInfo, this->tileManager, this->objectSpawner);
    
    this->header = std::make_unique<Header>();
}

void Game::initRobot(){
    this->robot = Robot(200, 200);
}

Game::Game(GamePanelInfo* gpInfo)
{
    this->initVariables(gpInfo);
    this->initRobot();
}

Game::~Game()
{
}


void Game::updateWindowCollision()
{
    float window_width = gamePanelInfo->screenWidth;
    float window_heigth = gamePanelInfo->screenHeight;
    
    //Left Bound
    if(this->robot.getBounds().left < 0.f)
    {
        this->robot.setPosition(0.f, this->robot.getBounds().top);
        std::cout << "Window Collision!!" << std::endl;
    }
    
    //Right bound
    else if(this->robot.getBounds().left + this->robot.getBounds().width > window_width )
    {
        this->robot.setPosition(window_width - this->robot.getBounds().width, this->robot.getBounds().top);
        std::cout << "Window Collision!!" << std::endl;
    }
    
    //Top Bound
    if(this->robot.getBounds().top < 0.f)
    {
        this->robot.setPosition(this->robot.getBounds().left, 0.f);
        std::cout << "Window Collision!!" << std::endl;
    }
    //Bottom Bound
    else if(this->robot.getBounds().top + this->robot.getBounds().height > window_heigth)
    {

        this->robot.setPosition(this->robot.getBounds().left, window_heigth- this->robot.getBounds().height);
        std::cout << "Window Collision!!" << std::endl;
    }
}

void Game::update(){
    

    if(this->mode == INGAME)
    {
        this->robot.update(this->collisionChecker);

        this->objectSpawner->update(this->tileManager, &this->robot);

        this->header->update(this->robot.getPoints());

        this->updateWindowCollision();
    }
}


void Game::render(sf::RenderTarget* target){

    this->tileManager->render(target);

    //Draw Game
    this->objectSpawner->render(target);

    this->robot.render(target);

    this->header->render(target);
}



