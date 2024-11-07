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
    public:
        ObjectSpawner();

        int max_number_powerUps = 1;
        int current_powerUps = 0;

        chrono::time_point<chrono::steady_clock> lastTimeUpdate_powerups = chrono::steady_clock::now();
        chrono::seconds updateInterval_powerups = std::chrono::seconds(5);

        chrono::time_point<chrono::steady_clock> lastTimeUpdate_points = chrono::steady_clock::now();
        chrono::milliseconds updateInterval_points = std::chrono::milliseconds(1600);

        vector<SuperObject*> powerUps;

        vector<SuperObject*> points;
        
        unsigned int max_point_objs = 10;

        
        void removeObject(int idx, bool powerUp);
        void addObject(SuperObject* object, bool powerUp);
        bool checkObjectIntersection(SuperObject* object);
        void spawnObject(SuperObject* ,TileManager*, Entity*, bool);
        PowerUpObject* generateRandomPowerUp();

        void update(TileManager* tilesManager, Entity* robot);
        void render(sf::RenderTarget* target);

};

#endif