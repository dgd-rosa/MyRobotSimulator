#include "entities/entity.hpp"
#include "tiles/tileManager.hpp"
#include "exceptions/GameException.hpp"
#include "objects/object_spawner.hpp"
#include <cmath>

#ifndef COLLISIONCHECKER_HPP
#define COLLISIONCHECKER_HPP


class CollisionChecker
{
    public:
        GamePanelInfo* gpInfo;
        TileManager* tileManager;
        ObjectSpawner* objSpawner;
        
        CollisionChecker(GamePanelInfo* gpInfo, TileManager* tileManager, ObjectSpawner* objSpawner);

        bool checkTile(Entity* entity);
        bool checkTileLine(int low_idx, int high_idx, int stable_idx, bool horizontal);
        bool checkWindowCollision(Entity* entity);
        int checkObject(Entity* entity, bool player, bool is_powerUp);
};

#endif
