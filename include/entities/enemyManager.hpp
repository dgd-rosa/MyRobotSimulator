#include "entities/enemy.hpp"
#include "tiles/tileManager.hpp"

#ifndef ENEMY_MANAGER_HPP
#define ENEMY_MANAGER_HPP


class EnemyManager
{
    private:
        std::vector<Enemy*> enemyList;
        unsigned int current_enemy_number;

        chrono::milliseconds enemy_spawn_cooldown;
        chrono::time_point<chrono::steady_clock> lastSpawn = chrono::steady_clock::now();

        int maxNumberEnemy;

        std::weak_ptr<SoundManager> soundManager;
        

        void initConfigFile();

    public:
        EnemyManager(std::shared_ptr<SoundManager>);
        ~EnemyManager() = default;


        void addEnemy(Enemy* enemy);
        void removeEnemy(unsigned int idx);
        void spawnNewEnemy(Robot* robot, TileManager* tilesManager);
        bool checkEnemyIntersection(Enemy* enemy);
        bool checkTileIntersection(Enemy* enemy, TileManager* tilesManager);
        bool checkEnemyNumber();

        //Acessors
        std::vector<Enemy*> getEnemyList();
        std::vector<Projectile*> shootEnemyListToRobot(Robot* robot);

        void updateEnemies(Robot *, TileManager* tilesManager);
        void moveEnemies();
        
        void renderEnemies(sf::RenderTarget* target);
};


#endif