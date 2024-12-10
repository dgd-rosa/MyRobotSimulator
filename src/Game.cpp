#include "Game.hpp"


// Private Functions

void Game::initVariables(GamePanelInfo* gpInfo, std::shared_ptr<SoundManager> soundManager)
{
    
    this->gamePanelInfo = gpInfo;

    this->tileManager = new TileManager(gamePanelInfo);


    this->projectileManager = std::make_unique<ProjectileManager>();

    this->soundManager = soundManager;
    this->enemyManager = std::make_unique<EnemyManager>(soundManager);
    this->enemyManager->addEnemy(new EnemyMedium(120.f, 460.f, this->soundManager));
    
    this->objectSpawner = new ObjectSpawner(this->tileManager);
    
    this->collisionChecker = new CollisionChecker(this->gamePanelInfo, this->tileManager, this->objectSpawner);
    
    //TODO: change this hard coded value
    this->header = std::make_unique<Header>(6, this->gamePanelInfo->tileSize);
}

void Game::initRobot(){
    this->robot = Robot(200, 200, this->soundManager);
}

void Game::initText()
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


    //GameOver Text
    this->gameOverText.setFont(font);
    this->gameOverText.setCharacterSize(50);
    this->gameOverText.setFillColor(sf::Color::Yellow);
    this->gameOverText.setOutlineColor(sf::Color::Black);
    this->gameOverText.setString("Game Over");

    auto gameOverTextBounds = this->gameOverText.getLocalBounds();
    this->gameOverText.setOrigin(gameOverTextBounds.width / 2, gameOverTextBounds.height / 2);
    this->gameOverText.setPosition(screenWidth / 2 , screenHeight / 2);
    
    

    this->pauseBackground.setSize(sf::Vector2f(this->gamePanelInfo->screenWidth, this->gamePanelInfo->screenHeight));
    this->pauseBackground.setPosition(sf::Vector2f(0.f, 0.f));
    this->pauseBackground.setFillColor(sf::Color(128, 128, 128, 150));
}



Game::Game(GamePanelInfo* gpInfo, std::shared_ptr<SoundManager> soundManager)
    : robot(100.0f, 200.0f, soundManager)
{
    this->initVariables(gpInfo, soundManager);
    this->initRobot();
    this->initText();

    this->initTime = chrono::steady_clock::now();
}

Game::~Game()
{
    this->enemyManager.reset();
    this->header.reset();
    this->projectileManager.reset();
    
    this->soundManager.reset();
    
    
    delete this->objectSpawner;
    delete this->tileManager;
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
    this->collisionChecker->checkRobotHitEnemies(&this->robot, this->enemyManager->getEnemyList());
    this->collisionChecker->checkObstacles(&this->robot);


    //enemies
    this->collisionChecker->checkEnemyListObstacles(this->enemyManager);

    //Projectiles
    this->collisionChecker->checkProjectilesObstacles(this->projectileManager);


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
    if(this->robot.getLifePoints() <= 0)
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

Score Game::getScore()
{
    Score score;
    score.level = this->robot.getLevel();
    score.score = this->robot.getPoints();

    this->finishTime = chrono::steady_clock::now();
    auto interval = chrono::duration_cast<chrono::seconds>(this->initTime - this->finishTime);
    score.time = interval.count();

    return score;
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
        this->enemyManager->updateEnemies(&this->robot, this->objectSpawner, this->tileManager);

        this->shootProjectiles();

        this->projectileManager->updateProjectiles(this->gamePanelInfo->screenWidth, this->gamePanelInfo->screenHeight);
        this->updateCollisions();

        if(enemyManager->checkEnemyNumber())
        {
            std::cout << "Robot Killed an enemy!!!" << std::endl; 
        }

        // Updates
        this->robot.update();
        this->enemyManager->moveEnemies();
        this->objectSpawner->update(this->tileManager, &this->robot);
        this->header->update(this->robot.getPoints(), this->robot.getLevel(), this->robot.getLifePoints());


        this->updateWindowCollision();

        this->checkGameOver();
    }

    if(this->mode == GAME_OVER)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {

        }
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
    else if(this->mode == GAME_OVER)
    {
        target->draw(this->pauseBackground);
        target->draw(this->gameOverText);
    }
}



