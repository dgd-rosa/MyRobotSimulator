#include "ProjectileManager.hpp"

ProjectileManager::ProjectileManager()
{
}

ProjectileManager::~ProjectileManager()
{
}

std::vector<Projectile*>& ProjectileManager::getRobotProjectiles()
{
    return this->robotProjectiles;
}

std::vector<Projectile*>& ProjectileManager::getEnemyProjectiles()
{
    return this->enemyProjectiles;
}

void ProjectileManager::addRobotProjectile(Projectile* projectile)
{
    if(projectile == nullptr)
        return;
    
    this->robotProjectiles.push_back(projectile);
}

void ProjectileManager::addEnemyProjectile(Projectile* projectile)
{
    if(projectile == nullptr)
        return;
    
    this->enemyProjectiles.push_back(projectile);
}

void ProjectileManager::addEnemyListProjectile(std::vector<Projectile*> projectileList)
{
    if(projectileList.size() == 0)
        return;

    for(Projectile* proj : projectileList)
    {
        if(proj == nullptr)
            continue;
        

        this->addEnemyProjectile(proj);
    }

}

void ProjectileManager::removeRobotProjectile(unsigned int idx)
{
    //access index out of scope
    if(idx >= this->robotProjectiles.size())
    {
        return;
    }

    delete this->robotProjectiles[idx];
    this->robotProjectiles.erase(this->robotProjectiles.begin() + idx);
}

void ProjectileManager::removeEnemyProjectile(unsigned int idx)
{
    //access index out of scope
    if(idx >= this->enemyProjectiles.size())
    {
        return;
    }

    delete this->enemyProjectiles[idx];
    this->enemyProjectiles.erase(this->enemyProjectiles.begin() + idx);

}

void ProjectileManager::updateProjectiles(float screenWidth, float screenHeight)
{
    unsigned counter = 0;
    for(auto projectile: this->enemyProjectiles)
    {
        projectile->update();

        // delete bullet out of bounds
        if(projectile->getPos().x < 0.f || projectile->getPos().x > screenWidth)
        {
            this->removeEnemyProjectile(counter);
            --counter;
        }

        ++counter;
    }


    counter = 0;
    for(auto projectile: this->robotProjectiles)
    {
        projectile->update();

        // delete bullet out of bounds
        if(projectile->getPos().x < 0.f || projectile->getPos().x > screenWidth ||
            projectile->getPos().y < 0.f || projectile->getPos().y > screenHeight)
        {
            this->removeRobotProjectile(counter);
            --counter;
        }

        ++counter;
    }
}

void ProjectileManager::renderProjectiles(sf::RenderTarget* target)
{
    if(target == nullptr)
    {
        return;
    }

    //draw enemy projectiles
    if(this->enemyProjectiles.size() > 0)
    {
        for(auto proj : this->enemyProjectiles)
        {
            proj->render(target);
        }
    }

    //draw robot projectiles
    if(this->robotProjectiles.size() > 0)
    {
        for(auto proj : this->robotProjectiles)
        {
            proj->render(target);
        }
    }
}