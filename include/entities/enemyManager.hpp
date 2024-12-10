#include "entities/enemy.hpp"
#include "tiles/tileManager.hpp"
#include "objects/object_spawner.hpp"

#ifndef ENEMY_MANAGER_HPP
#define ENEMY_MANAGER_HPP

struct Difficulty
{
    int spawnEnemyCooldown;
    int weakEnemyProbability;
    int mediumEnemyProbability;
    int strongEnemyProbability;
};

class EnemyManager
{
    private:
        std::vector<Enemy*> enemyList;
        unsigned int current_enemy_number;

        chrono::milliseconds difficultIncreaseTime;
        chrono::time_point<chrono::steady_clock> lastDifficultIncreaseTime = chrono::steady_clock::now();
        std::vector<std::pair<int, Difficulty>> difficultiesList;
        int current_difficulty = 1;

        chrono::milliseconds enemy_spawn_cooldown;
        chrono::time_point<chrono::steady_clock> lastSpawn = chrono::steady_clock::now();

        int maxNumberEnemy;
        int probabilty_loot = 50;

        float weak_enemy_spawn_probability = 100;
        float medium_enemy_spawn_probability = 0;
        float strong_enemy_spawn_probability = 0;
        std::vector<std::pair<EnemyType, float>> enemyProbabilities;

        std::weak_ptr<SoundManager> soundManager;
        

        void initConfigFile();
        void initDifficulties(json config);
        void increaseDifficulty();
        

    public:
        EnemyManager(std::shared_ptr<SoundManager>);
        ~EnemyManager() = default;


        void addEnemy(Enemy* enemy);
        void removeEnemy(unsigned int idx);
        EnemyType chooseRandomEnemyType();
        Enemy* generateRandomEnemy();
        void spawnNewEnemy(Robot* robot, TileManager* tilesManager);
        bool checkEnemyIntersection(Enemy* enemy);
        bool checkTileIntersection(Enemy* enemy, TileManager* tilesManager);
        bool checkEnemyNumber();

        //Acessors
        std::vector<Enemy*> getEnemyList();
        std::vector<Projectile*> shootEnemyListToRobot(Robot* robot);

        void updateEnemies(Robot *, ObjectSpawner* objectSpawner, TileManager* tilesManager);
        void moveEnemies();
        
        void renderEnemies(sf::RenderTarget* target);
};


#endif