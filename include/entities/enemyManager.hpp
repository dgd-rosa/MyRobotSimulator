#include "entities/enemy.hpp"
#include "tiles/tileManager.hpp"
#include "objects/object_spawner.hpp"
#include "menu/text_disappearing.hpp"

#ifndef ENEMY_MANAGER_HPP
#define ENEMY_MANAGER_HPP

class EnemyManager
{
    private:
        std::vector<Enemy*> enemyList;
        unsigned int current_enemy_number;

        chrono::milliseconds difficultIncreaseTime;
        chrono::time_point<chrono::steady_clock> lastDifficultIncreaseTime = chrono::steady_clock::now();
        int current_difficulty = 1;

        chrono::milliseconds enemy_spawn_cooldown;
        chrono::time_point<chrono::steady_clock> lastSpawn = chrono::steady_clock::now();

        int maxNumberEnemy;
        int probabilty_loot = 50;
        std::map<EnemyType, float> enemyProbabilitiesMap;
        std::map<EnemyType, float> enemyMaxProbabilitiesMap;
        float difficultyFactor = 0;

        
        std::weak_ptr<SoundManager> soundManager;

        std::vector<std::unique_ptr<TextDisappear>> text_disappearing_list;

        void initConfigFile();
        void initDifficulties(json config);
        void adjustDifficulty(float difficultyFactor);
        void increaseDifficultyFactor(int playerScore);

        //Text disappearing
        void addTextDisappearing(Enemy* enemy);
        void removeTextDisappearing(int idx);
        void updateTextDisappearing();

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