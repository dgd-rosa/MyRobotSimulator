#include "tiles/tileManager.hpp"
#include "exceptions/GameException.hpp"
#include "objects/object_spawner.hpp"
#include "ProjectileManager.hpp"
#include "entities/enemyManager.hpp"
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
        void checkObstacles(Entity* entity);
        void checkEntities(Entity* entity1, Entity* entity2);
        bool checkTileLine(int low_idx, int high_idx, int stable_idx, bool horizontal);
        bool checkWindowCollision(Entity* entity);



        void checkObjects(Entity* entity, std::vector<SuperObject*>& object_list);
        void checkRobotProjectiles(Entity* entity, unique_ptr<ProjectileManager> &projectileManager);
        void checkRobotHitByProjectiles(Entity* entity, unique_ptr<ProjectileManager> &projectileManager);
        void checkRobotHitEnemies(Entity* entity, std::vector<Enemy*> enemies);
        void checkEnemyListHitByProjectiles(unique_ptr<EnemyManager> &enemyManager, unique_ptr<ProjectileManager> &projectileManager);
        void checkEnemyListObstacles(unique_ptr<EnemyManager> &enemyManager);
};  

#endif
