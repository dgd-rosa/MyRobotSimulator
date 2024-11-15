#include "entities/enemyManager.hpp"

EnemyManager::EnemyManager()
{
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

        std::cout << "Projectile Damage: " << projectile->damage << std::endl;

        projectileList.push_back(projectile);        
    }

    return projectileList;
}

void EnemyManager::updateEnemies(Robot* robot)
{
    //check if each enemy died
    unsigned int counter = 0;
    for(auto enemy : this->enemyList)
    {
        if(enemy->isDead())
        {
            std::cout << "Enemy is Dead" << std::endl;
            this->removeEnemy(counter);
            --counter;
        }
        ++counter;
    }


    //TODO: Update Enemy Movement
    for(auto enemy : this->enemyList)
    {
        enemy->updateMovement(robot);
    }
}

void EnemyManager::renderEnemies(sf::RenderTarget* target)
{
    for(auto enemy : this->enemyList)
    {
        enemy->render(target);
    }
}
