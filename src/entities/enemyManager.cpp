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
    this->probabilty_loot = config["EnemyManager"]["probabilityLoot"];

    cooldown = config["EnemyManager"]["difficultIncreaseTime"];
    this->difficultIncreaseTime = std::chrono::milliseconds(cooldown);

    //Enemy Probability Spawn
    this->enemyProbabilities.push_back(std::make_pair(WEAK, config["EnemyManager"]["weak_probability"]));
    this->enemyProbabilities.push_back(std::make_pair(MEDIUM, config["EnemyManager"]["medium_probability"]));
    this->enemyProbabilities.push_back(std::make_pair(STRONG, config["EnemyManager"]["strong_probability"]));

    this->initDifficulties(config);
}

void EnemyManager::initDifficulties(json config)
{
    Difficulty difficulty1;
    difficulty1.spawnEnemyCooldown = config["EnemyManager"]["Difficulty"]["1"]["enemySpawnCooldown"];
    difficulty1.weakEnemyProbability = config["EnemyManager"]["Difficulty"]["1"]["weak_probability"];
    difficulty1.mediumEnemyProbability = config["EnemyManager"]["Difficulty"]["1"]["medium_probability"];
    difficulty1.strongEnemyProbability = config["EnemyManager"]["Difficulty"]["1"]["strong_probability"];


    Difficulty difficulty2;
    difficulty2.spawnEnemyCooldown = config["EnemyManager"]["Difficulty"]["2"]["enemySpawnCooldown"];
    difficulty2.weakEnemyProbability = config["EnemyManager"]["Difficulty"]["2"]["weak_probability"];
    difficulty2.mediumEnemyProbability = config["EnemyManager"]["Difficulty"]["2"]["medium_probability"];
    difficulty2.strongEnemyProbability = config["EnemyManager"]["Difficulty"]["2"]["strong_probability"];



    Difficulty difficulty3;
    difficulty3.spawnEnemyCooldown = config["EnemyManager"]["Difficulty"]["3"]["enemySpawnCooldown"];
    difficulty3.weakEnemyProbability = config["EnemyManager"]["Difficulty"]["3"]["weak_probability"];
    difficulty3.mediumEnemyProbability = config["EnemyManager"]["Difficulty"]["3"]["medium_probability"];
    difficulty3.strongEnemyProbability = config["EnemyManager"]["Difficulty"]["3"]["strong_probability"];


    Difficulty difficulty4;
    difficulty4.spawnEnemyCooldown = config["EnemyManager"]["Difficulty"]["4"]["enemySpawnCooldown"];
    difficulty4.weakEnemyProbability = config["EnemyManager"]["Difficulty"]["4"]["weak_probability"];
    difficulty4.mediumEnemyProbability = config["EnemyManager"]["Difficulty"]["4"]["medium_probability"];
    difficulty4.strongEnemyProbability = config["EnemyManager"]["Difficulty"]["4"]["strong_probability"];


    Difficulty difficulty5;
    difficulty5.spawnEnemyCooldown = config["EnemyManager"]["Difficulty"]["5"]["enemySpawnCooldown"];
    difficulty5.weakEnemyProbability = config["EnemyManager"]["Difficulty"]["5"]["weak_probability"];
    difficulty5.mediumEnemyProbability = config["EnemyManager"]["Difficulty"]["5"]["medium_probability"];
    difficulty5.strongEnemyProbability = config["EnemyManager"]["Difficulty"]["5"]["strong_probability"];



    Difficulty difficulty6;
    difficulty6.spawnEnemyCooldown = config["EnemyManager"]["Difficulty"]["6"]["enemySpawnCooldown"];
    difficulty6.weakEnemyProbability = config["EnemyManager"]["Difficulty"]["6"]["weak_probability"];
    difficulty6.mediumEnemyProbability = config["EnemyManager"]["Difficulty"]["6"]["medium_probability"];
    difficulty6.strongEnemyProbability = config["EnemyManager"]["Difficulty"]["6"]["strong_probability"];


    Difficulty difficulty7;
    difficulty7.spawnEnemyCooldown = config["EnemyManager"]["Difficulty"]["7"]["enemySpawnCooldown"];
    difficulty7.weakEnemyProbability = config["EnemyManager"]["Difficulty"]["7"]["weak_probability"];
    difficulty7.mediumEnemyProbability = config["EnemyManager"]["Difficulty"]["7"]["medium_probability"];
    difficulty7.strongEnemyProbability = config["EnemyManager"]["Difficulty"]["7"]["strong_probability"];

    this->difficultiesList.push_back(std::make_pair(1, difficulty1));
    this->difficultiesList.push_back(std::make_pair(2, difficulty2));
    this->difficultiesList.push_back(std::make_pair(3, difficulty3));
    this->difficultiesList.push_back(std::make_pair(4, difficulty4));
    this->difficultiesList.push_back(std::make_pair(5, difficulty5));
    this->difficultiesList.push_back(std::make_pair(6, difficulty6));
    this->difficultiesList.push_back(std::make_pair(7, difficulty7));
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
 *      Method to generate a random enemy Type according with the probabilities:
 *          
 *          Enemy Types:
 *              -Weak
 *              -Medium
 *              -Strong
 */

EnemyType EnemyManager::chooseRandomEnemyType()
{
    int random_number = rand() % 100;

    int cumulativeProbability = 0;

    for(auto pair : this->enemyProbabilities)
    {
        int probability = pair.second;
        EnemyType type = pair.first;

        cumulativeProbability += probability;
        if(random_number < cumulativeProbability)
        {
            return type;
        }
    }

}

/**
 *      Method to generate a random enemy according with the probabilities:
 *          
 *          @return New Enemy*
 */

Enemy* EnemyManager::generateRandomEnemy()
{
    EnemyType type = this->chooseRandomEnemyType();

    switch (type)
    {
    case WEAK:
        cout << "Generated WEAK" << endl;
        return new EnemyWeak(0.f, 0.f, this->soundManager);
        break;
    case MEDIUM:
        cout << "Generated MEDIUM" << endl;
        return new EnemyMedium(0.f, 0.f, this->soundManager);
        break;
    case STRONG:
        cout << "Generated STRONG" << endl;
        return new EnemyStrong(0.f, 0.f, this->soundManager);
        break;
    default:
        cout << "Generated WEAK (DEFAULT)" << endl;
        return new EnemyWeak(0.f, 0.f, this->soundManager);
        break;
    }
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

    Enemy* newEnemy = this->generateRandomEnemy();
    
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
    int row_idx = std::floor(enemy->getCollisionBounds().top / tileSize);
    int col_idx = std::floor(enemy->getCollisionBounds().left /tileSize);

    //Row or Col might be out of scope
    if(row_idx >= tilesManager->gpInfo->maxScreenRow || col_idx >= tilesManager->gpInfo->maxScreenCol)
        return true;

    int tile_number = tilesManager->getMap()[row_idx][col_idx];
    if(tilesManager->getTiles()[tile_number]->collision)
        return true;


    //Check Top right
    row_idx = enemy->getCollisionBounds().top/ tileSize;
    col_idx = (enemy->getCollisionBounds().left + enemy->getCollisionBounds().width) /tileSize;

    if(row_idx >= tilesManager->gpInfo->maxScreenRow || col_idx >= tilesManager->gpInfo->maxScreenCol)
        return true;

    tile_number = tilesManager->getMap()[row_idx][col_idx];
    if(tilesManager->getTiles()[tile_number]->collision)
        return true;


    //Check Bottom Left
    row_idx = (enemy->getCollisionBounds().top + enemy->getCollisionBounds().height)/ tileSize;
    col_idx = enemy->getCollisionBounds().left /tileSize;

    if(row_idx >= tilesManager->gpInfo->maxScreenRow || col_idx >= tilesManager->gpInfo->maxScreenCol)
        return true;

    tile_number = tilesManager->getMap()[row_idx][col_idx];
    if(tilesManager->getTiles()[tile_number]->collision)
        return true;


    //Check Bottom Right
    row_idx = (enemy->getCollisionBounds().top + enemy->getCollisionBounds().height) / tileSize;
    col_idx = (enemy->getCollisionBounds().left + enemy->getCollisionBounds().width) /tileSize;

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

void EnemyManager::increaseDifficulty()
{
    if(current_difficulty < 8)
    {
        current_difficulty += 1;
    }

    cout << "Increasing Difficulty to.... " << this->current_difficulty << endl;

    for(auto diff: this->difficultiesList)
    {
        if(diff.first == current_difficulty)
        {
            this->weak_enemy_spawn_probability = diff.second.weakEnemyProbability;
            this->medium_enemy_spawn_probability = diff.second.mediumEnemyProbability;
            this->strong_enemy_spawn_probability = diff.second.strongEnemyProbability;
            this->enemy_spawn_cooldown = chrono::milliseconds(diff.second.spawnEnemyCooldown);
        }
    }
}

void EnemyManager::updateEnemies(Robot* robot, ObjectSpawner* objectSpawner, TileManager* tilesManager)
{
    //check if each enemy died
    unsigned int counter = 0;
    for(auto enemy : this->enemyList)
    {
        if(enemy->isDead())
        {
            if(enemy->alive == false && enemy->dying == false)
            {
                //Drop Loot when enemy dies
                if (rand() % 100 < this->probabilty_loot)
                {
                    objectSpawner->spawnRandomPowerUp(enemy->getCollisionBounds().left, enemy->getCollisionBounds().top);
                }

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

   
    if(now - lastDifficultIncreaseTime > this->difficultIncreaseTime)
    {
        this->increaseDifficulty();
        this->lastDifficultIncreaseTime = now;
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
