#include "entities/enemyManager.hpp"

EnemyManager::EnemyManager(std::shared_ptr<SoundManager> soundManager)
{
    this->initConfigFile();
    current_enemy_number = 0;
    this->soundManager = soundManager;
}

void EnemyManager::initConfigFile()
{
    // Open the JSON file
    std::ifstream file("config.json");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config.json" << std::endl;
        return;
    }

    // Parse the JSON file
    json config;
    try {
        file >> config;
    } catch (const json::parse_error& e) {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
        return;
    }

    int cooldown = config["EnemyManager"]["enemySpawnCooldown"];
    this->enemy_spawn_cooldown = std::chrono::milliseconds(cooldown);
    this->maxNumberEnemy = config["EnemyManager"]["maxNumberEnemy"];
}

/**
 *      Method to add enemy to enemy List
 */
void EnemyManager::addEnemy(Enemy* enemy)
{
    if(enemy == nullptr)
    {
        return;
    }

    this->enemyList.push_back(enemy);
}


/**
 *      Method to remove enemy in index idx from enemy List
 */
void EnemyManager::removeEnemy(unsigned int idx)
{
    if(idx >= this->enemyList.size())
    {
        return;
    }

    delete this->enemyList[idx];
    this->enemyList.erase(this->enemyList.begin() + idx);
}

std::vector<Enemy*> EnemyManager::getEnemyList()
{
    return this->enemyList;
}


std::vector<Projectile*> EnemyManager::shootEnemyListToRobot(Robot* robot)
{
    std::vector<Projectile*> projectileList;

    for(Enemy* enemy : this->enemyList)
    {
        Projectile* projectile = enemy->shootToRobot(robot);
        if(projectile == nullptr)
            continue;

        projectileList.push_back(projectile);        
    }

    return projectileList;
}

bool EnemyManager::checkEnemyIntersection(Enemy* newEnemy)
{
    for(Enemy* enemy : this->enemyList)
    {
        if(newEnemy->getBounds().intersects(enemy->getBounds()))
        {
            return false;
        }
    }
    return true;
}

/**
 *      Method to spawn a new enemy after a cooldown
 */

void EnemyManager::spawnNewEnemy(Robot* robot, TileManager* tilesManager)
{
    if(tilesManager == nullptr || robot == nullptr)
    {
        throw GameException("Cannot spawn Enemy!!");
    }

    int screenWidth = tilesManager->gpInfo->screenWidth;
    int screenHeight = tilesManager->gpInfo->screenHeight;

    bool occupied = true;

    int enemy_top_left_x=0, enemy_top_left_y = 0;

    Enemy* newEnemy = new Enemy(0.f, 0.f, this->soundManager);
    
    while(occupied)
    {
        enemy_top_left_y = rand() % (screenHeight-1);
        enemy_top_left_x = rand() % (screenWidth-1);

        newEnemy->setPosition(sf::Vector2f(enemy_top_left_x, enemy_top_left_y));

        //Check if the Enemy is in a passable tile
        if(this->checkTileIntersection(newEnemy, tilesManager))
            continue;
          
        
        //if object is where the robot is (skip)
        if(newEnemy->getBounds().intersects(robot->getBounds()))
            continue;

        
        //Check if the position is valid for the existing objects
        //If the value is not valid then skip
        if(!this->checkEnemyIntersection(newEnemy))
            continue;
        

        //after everything we can make sure it is not occupied
        occupied = false;
    }

    //Add object to the vector
    this->addEnemy(newEnemy);
    
}

bool EnemyManager::checkTileIntersection(Enemy* enemy, TileManager* tilesManager)
{
    if(enemy == nullptr || tilesManager == nullptr)
        return false;
    
    int tileSize = tilesManager->gpInfo->tileSize;

    //Check Top Left
    int row_idx = std::floor(enemy->getBounds().top / tileSize);
    int col_idx = std::floor(enemy->getBounds().left /tileSize);

    //Row or Col might be out of scope
    if(row_idx >= tilesManager->gpInfo->maxScreenRow || col_idx >= tilesManager->gpInfo->maxScreenCol)
        return true;

    int tile_number = tilesManager->getMap()[row_idx][col_idx];
    if(tilesManager->getTiles()[tile_number]->collision)
        return true;


    //Check Top right
    row_idx = enemy->getBounds().top/ tileSize;
    col_idx = (enemy->getBounds().left + enemy->getBounds().width) /tileSize;

    if(row_idx >= tilesManager->gpInfo->maxScreenRow || col_idx >= tilesManager->gpInfo->maxScreenCol)
        return true;

    tile_number = tilesManager->getMap()[row_idx][col_idx];
    if(tilesManager->getTiles()[tile_number]->collision)
        return true;


    //Check Bottom Left
    row_idx = (enemy->getBounds().top + enemy->getBounds().height)/ tileSize;
    col_idx = enemy->getBounds().left /tileSize;

    if(row_idx >= tilesManager->gpInfo->maxScreenRow || col_idx >= tilesManager->gpInfo->maxScreenCol)
        return true;

    tile_number = tilesManager->getMap()[row_idx][col_idx];
    if(tilesManager->getTiles()[tile_number]->collision)
        return true;


    //Check Bottom Right
    row_idx = (enemy->getBounds().top + enemy->getBounds().height) / tileSize;
    col_idx = (enemy->getBounds().left + enemy->getBounds().width) /tileSize;

    if(row_idx >= tilesManager->gpInfo->maxScreenRow || col_idx >= tilesManager->gpInfo->maxScreenCol)
        return true;

    tile_number = tilesManager->getMap()[row_idx][col_idx];
    if(tilesManager->getTiles()[tile_number]->collision)
        return true;

    return false;
}

bool EnemyManager::checkEnemyNumber()
{
    bool enemyDead = false;
    if(this->enemyList.size() < this->current_enemy_number)
    {
        enemyDead = true;
    }
    this->current_enemy_number = this->enemyList.size();

    return enemyDead;
}

void EnemyManager::updateEnemies(Robot* robot, TileManager* tilesManager)
{
    //check if each enemy died
    unsigned int counter = 0;
    for(auto enemy : this->enemyList)
    {
        if(enemy->isDead())
        {
            if(enemy->alive == false && enemy->dying == false)
            {
                this->removeEnemy(counter);
                --counter;
                continue;
            }

            if(enemy->dying == false)
            {
                enemy->dying = true;
            }

        }
        ++counter;
    }

    

    //Spawn new Enemies if cooldown is over
    auto now = chrono::steady_clock::now();

    if(now - this->lastSpawn > this->enemy_spawn_cooldown)
    {
        //Make a new enemy
        this->spawnNewEnemy(robot, tilesManager);
        this->lastSpawn = now;
    }
    

    for(auto enemy : this->enemyList)
    {
        enemy->update(robot);
    }
}

void EnemyManager::moveEnemies()
{
    for(auto enemy : this->enemyList)
    {
        enemy->moveEnemy();
    }
}

void EnemyManager::renderEnemies(sf::RenderTarget* target)
{
    for(auto enemy : this->enemyList)
    {
        enemy->render(target);
    }
}
