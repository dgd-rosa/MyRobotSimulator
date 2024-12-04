#include "OBJ_BatteryBoost.hpp"
#include "OBJ_Screw.hpp"
#include "tiles/tileManager.hpp"
#include "entities/entity.hpp"

#include <vector>
#include <chrono>

using namespace std;

#ifndef OBJECTSPAWNER_HPP
#define OBJECTSPAWNER_HPP



class ObjectSpawner
{
    private:
        void initConfigFile();
    public:
        ObjectSpawner();

        int max_number_powerUps = 1;
        int current_powerUps = 0;

        chrono::time_point<chrono::steady_clock> lastTimeUpdate_powerups = chrono::steady_clock::now();
        chrono::milliseconds powerup_spawn_cooldown;

        chrono::time_point<chrono::steady_clock> lastTimeUpdate_points = chrono::steady_clock::now();
        chrono::milliseconds screw_spawn_cooldown;

        vector<SuperObject*> powerUps;

        vector<SuperObject*> points;
        
        unsigned int max_number_screws = 10;

        
        void removeObject(int idx, bool powerUp);
        void addObject(SuperObject* object, bool powerUp);
        bool checkObjectIntersection(SuperObject* object);
        void spawnObject(SuperObject* ,TileManager*, Entity*, bool);
        PowerUpObject* generateRandomPowerUp();

        void update(TileManager* tilesManager, Entity* robot);
        void render(sf::RenderTarget* target);

};

#endif