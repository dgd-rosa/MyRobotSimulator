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


    this->enemyProbabilitiesMap.insert({WEAK, config["EnemyManager"]["weak_probability"]});
    this->enemyProbabilitiesMap.insert({MEDIUM, config["EnemyManager"]["medium_probability"]});
    this->enemyProbabilitiesMap.insert({STRONG, config["EnemyManager"]["strong_probability"]});

    this->enemyMaxProbabilitiesMap.insert({WEAK, config["EnemyManager"]["max_weak_probability"]});
    this->enemyMaxProbabilitiesMap.insert({MEDIUM, config["EnemyManager"]["max_medium_probability"]});
    this->enemyMaxProbabilitiesMap.insert({STRONG, config["EnemyManager"]["max_strong_probability"]});
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

    for(auto& [key, value] : this->enemyProbabilitiesMap)
    {
        int probability = value;
        EnemyType type = key;

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
        return new EnemyWeak(0.f, 0.f, this->soundManager);
        break;
    case MEDIUM:
        return new EnemyMedium(0.f, 0.f, this->soundManager);
        break;
    case STRONG:
        return new EnemyStrong(0.f, 0.f, this->soundManager);
        break;
    default:
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

void EnemyManager::adjustDifficulty(float difficultyFactor)
{
    cout << "OLD Probabilities (WEAK, MEDIUM, STRONG): ";
    cout << this->enemyProbabilitiesMap[WEAK] << "|";
    cout << this->enemyProbabilitiesMap[MEDIUM] << "|";
    cout << this->enemyProbabilitiesMap[STRONG] << endl;
    
    this->enemyProbabilitiesMap[WEAK] = std::max(10.f, enemyProbabilitiesMap[WEAK] - difficultyFactor * 0.3f);
    this->enemyProbabilitiesMap[MEDIUM] = std::min(enemyMaxProbabilitiesMap[MEDIUM], enemyProbabilitiesMap[MEDIUM] + difficultyFactor * 0.25f);
    //this->enemyProbabilitiesMap[STRONG] = std::min(enemyMaxProbabilitiesMap[STRONG], enemyProbabilitiesMap[STRONG] + difficultyFactor * 0.15f);
    this->enemyProbabilitiesMap[STRONG] = 100 - enemyProbabilitiesMap[WEAK] - enemyProbabilitiesMap[MEDIUM];

    cout << "NEW Probabilities (WEAK, MEDIUM, STRONG): ";
    cout << this->enemyProbabilitiesMap[WEAK] << "|";
    cout << this->enemyProbabilitiesMap[MEDIUM] << "|";
    cout << this->enemyProbabilitiesMap[STRONG] << endl;

    cout << "OLD spawn time";
    cout << this->enemy_spawn_cooldown.count();
    int cooldown = std::max(2000.f, this->enemy_spawn_cooldown.count() - difficultyFactor * 500);
    this->enemy_spawn_cooldown = chrono::milliseconds(cooldown);


    cout << "NEW spawn time";
    cout << this->enemy_spawn_cooldown.count();
}

void EnemyManager::increaseDifficultyFactor(int playerScore)
{
    int newDifficulty = playerScore / 100;
    if(newDifficulty > difficultyFactor)
    {
        this->difficultyFactor = newDifficulty;
    }
}

void EnemyManager::addTextDisappearing(Enemy* enemy)
{
    auto enemyBounds = enemy->getBounds();

    sf::Vector2f enemyCenter;
    enemyCenter.x = enemyBounds.left + enemyBounds.width/2;
    enemyCenter.y = enemyBounds.top;

    this->text_disappearing_list.push_back(
        std::make_unique<TextDisappear>(enemyCenter, enemy->getXPPoints())
    );

}

void EnemyManager::removeTextDisappearing(int idx)
{
    if(idx >= this->text_disappearing_list.size())
    {
        return;
    }

    this->text_disappearing_list.erase(this->text_disappearing_list.begin() + idx);
}

void EnemyManager::updateTextDisappearing()
{
    for (size_t idx = 0; idx < this->text_disappearing_list.size();)
    {
        auto &text = this->text_disappearing_list[idx];

        // Skip if text is nullptr (defensive programming)
        if (!text)
        {
            std::cerr << "Warning: nullptr detected in text_disappearing_list." << std::endl;
            this->text_disappearing_list.erase(this->text_disappearing_list.begin() + idx);
            continue; // Don't increment idx; the next item has shifted to current idx
        }

        // Check transparency
        if (text->getTransparency() <= 0)
        {
            // Remove text
            this->text_disappearing_list.erase(this->text_disappearing_list.begin() + idx);
            continue; // Don't increment idx
        }

        // Update text
        text->update();
        ++idx; // Increment only if no removal
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

                //Create TextDisappearing
                this->addTextDisappearing(enemy);

                //Update robot XP
                robot->increasePoints(enemy->getXPPoints());

                //Remove Enemy
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
        if(this->enemyList.size() < this->maxNumberEnemy)
        {
            //Make a new enemy
            this->spawnNewEnemy(robot, tilesManager);
        }
        this->lastSpawn = now;
    }
    
    for(auto enemy : this->enemyList)
    {
        enemy->update(robot);
    }

    float currentFactor = this->difficultyFactor;
    this->increaseDifficultyFactor(robot->getPoints());

    if(currentFactor != this->difficultyFactor)
    {
        this->adjustDifficulty(this->difficultyFactor);
    }


    //Text Disappearing
    this->updateTextDisappearing();
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

    for(auto &text : this->text_disappearing_list)
    {
        text->render(target);
    }
}
