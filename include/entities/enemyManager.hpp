#include "entities/enemy.hpp"

#ifndef ENEMY_MANAGER_HPP
#define ENEMY_MANAGER_HPP


class EnemyManager
{
    private:
        std::vector<Enemy*> enemyList;

    public:
        EnemyManager();
        ~EnemyManager() = default;


        void addEnemy(Enemy* enemy);
        void removeEnemy(unsigned int idx);

        //Acessors
        std::vector<Enemy*> getEnemyList();
        std::vector<Projectile*> shootEnemyListToRobot(Robot* robot);

        void updateEnemies(Robot *);
        void renderEnemies(sf::RenderTarget* target);
};


#endif