#include "Game.hpp"


// Private Functions

void Game::initVariables(GamePanelInfo* gpInfo){
    
    this->gamePanelInfo = gpInfo;

    this->tileManager = new TileManager(gamePanelInfo);


    this->projectileManager = std::make_unique<ProjectileManager>();

    this->enemyManager = std::make_unique<EnemyManager>();
    this->enemyManager->addEnemy(new Enemy(100.f, 243.f));
    this->enemyManager->addEnemy(new Enemy(400.f, 43.f));
    
    this->objectSpawner = new ObjectSpawner();
    
    this->collisionChecker = new CollisionChecker(this->gamePanelInfo, this->tileManager, this->objectSpawner);
    
    this->header = std::make_unique<Header>();
}

void Game::initRobot(){
    this->robot = Robot(200, 200);
}

void Game::initPauseText()
{

    if(!this->font.loadFromFile("fonts/yoster.ttf"))
    {
        throw GameException("error loading font file");
    }

    this->pauseText.setFont(font);
    this->pauseText.setCharacterSize(40);
    this->pauseText.setFillColor(sf::Color::Yellow);
    this->pauseText.setOutlineColor(sf::Color::Black);
    this->pauseText.setString("Paused");

    auto pauseTextBounds = this->pauseText.getLocalBounds();
    int screenWidth = this->gamePanelInfo->screenWidth;
    int screenHeight = this->gamePanelInfo->screenHeight;

    this->pauseText.setOrigin(pauseTextBounds.width / 2, pauseTextBounds.height / 2);

    this->pauseText.setPosition(screenWidth / 2 , screenHeight / 2);
    
    

    this->pauseBackground.setSize(sf::Vector2f(this->gamePanelInfo->screenWidth, this->gamePanelInfo->screenHeight));
    this->pauseBackground.setPosition(sf::Vector2f(0.f, 0.f));
    this->pauseBackground.setFillColor(sf::Color(128, 128, 128, 150));
}



Game::Game(GamePanelInfo* gpInfo)
{
    this->initVariables(gpInfo);
    this->initRobot();
    this->initPauseText();
}

Game::~Game()
{
    delete this->collisionChecker;
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


void Game::updateCollisions()
{
    //check for Obstacles collisions
    this->collisionChecker->checkObstacles(&this->robot);

    //enemies
    this->collisionChecker->checkEnemyListObstacles(this->enemyManager);


    //Check For objects
    //Robot
    this->collisionChecker->checkObjects(&this->robot, (this->objectSpawner->powerUps));
    this->collisionChecker->checkObjects(&this->robot, (this->objectSpawner->points));

    //Check For Projectiles
    this->collisionChecker->checkRobotHitByProjectiles(&this->robot, this->projectileManager); //robot
    this->collisionChecker->checkEnemyListHitByProjectiles(this->enemyManager, this->projectileManager); //enemies
}

void Game::checkGameOver()
{
    if(this->robot.getLifePoints() <= 0 || this->robot.getBatteryValue() <= 0)
    {
        //Game Over
        std::cout << "Game OVer !!!!!!!1" << std::endl;

        this->mode = GAME_OVER;
    }
}

void Game::pauseGame()
{
    this->mode = PAUSE;
}

void Game::resumeGame()
{
    this->mode = INGAME;
}

void Game::handleEnterPressed()
{
    if(this->mode == PAUSE)
    {
        this->resumeGame();
    }
    else if(this->mode == INGAME)
    {
        this->pauseGame();
    }
}


void Game::shootProjectiles()
{
    this->projectileManager->addRobotProjectile(this->robot.shoot());

    
    this->projectileManager->addEnemyListProjectile(this->enemyManager->shootEnemyListToRobot(&this->robot));
    
}

void Game::update(){

    if(this->mode == INGAME)
    {   

        this->robot.updateInput();

        this->enemyManager->updateEnemies(&this->robot);

        this->shootProjectiles();

        this->projectileManager->updateProjectiles(this->gamePanelInfo->screenWidth, this->gamePanelInfo->screenHeight);

        this->updateCollisions();

        // Updates
        this->robot.update();

        this->objectSpawner->update(this->tileManager, &this->robot);

        this->header->update(this->robot.getPoints());

        this->updateWindowCollision();

        //this->checkGameOver();
    }

    if(this->mode == GAME_OVER)
    {

    }
}

void Game::render(sf::RenderTarget* target){

    this->tileManager->render(target);

    //Draw Game
    this->objectSpawner->render(target);

    this->projectileManager->renderProjectiles(target);

    this->robot.render(target);

    this->enemyManager->renderEnemies(target);

    this->header->render(target);

    if(this->mode == PAUSE)
    {
        target->draw(this->pauseBackground);
        target->draw(this->pauseText);
    }
}



