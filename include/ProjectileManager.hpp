#include "objects/projectile.hpp"

#ifndef PROJECTILE_MANAGER_HPP
#define PROJECTILE_MANAGER_HPP

class ProjectileManager
{
    private:
        std::vector<Projectile*> enemyProjectiles;
        std::vector<Projectile*> robotProjectiles;

    public:
        ProjectileManager();
        ~ProjectileManager();

        void addRobotProjectile(Projectile* projectile);
        void addEnemyProjectile(Projectile* projectile);
        void addEnemyListProjectile(std::vector<Projectile*> projectile);
        void removeRobotProjectile(unsigned int idx);
        void removeEnemyProjectile(unsigned int idx);

        //Gets
        std::vector<Projectile*>& getRobotProjectiles();
        std::vector<Projectile*>& getEnemyProjectiles();

        void updateProjectiles(float screenWidth, float screenHeight);
        void renderProjectiles(sf::RenderTarget* target);
};

#endif