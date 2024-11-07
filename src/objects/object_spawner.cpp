#include "objects/object_spawner.hpp"

ObjectSpawner::ObjectSpawner()
{

}

void ObjectSpawner::update(TileManager* tilesManager, Entity* robot)
{
    auto now = std::chrono::steady_clock::now();

    //Points UPDATE
    if(now - this->lastTimeUpdate_points > this->updateInterval_points)
    {
        this->lastTimeUpdate_points = now;

        if(this->points.size() < this->max_point_objs)
        {
            //Generate Random Power Up -> chooses a random power up from the enum
            this->spawnObject(new OBJ_Screw(), tilesManager, robot, false);
        }
    }
    
    
    //POWER UPS Update
    if(now - this->lastTimeUpdate_powerups > this->updateInterval_powerups)
    {
        this->lastTimeUpdate_powerups = now;
        
        if(this->current_powerUps < this->max_number_powerUps)
        {
            //TODO: Create a function to randomize localiton
            //Generate Random Power Up -> chooses a random power up from the enum
            this->spawnObject(this->generateRandomPowerUp(), tilesManager, robot, true);
        }
    }

    
}

void ObjectSpawner::addObject(SuperObject* object, bool powerUp)
{
    if(powerUp)
    {
        this->powerUps.push_back(object);
        this->current_powerUps++;
    }
    else{
        this->points.push_back(object);
    }
}

void ObjectSpawner::removeObject(int idx, bool powerUp)
{
    if(powerUp)
    {
        this->current_powerUps--;

        //remove object
        delete this->powerUps[idx];
        this->powerUps[idx] = nullptr;
        this->powerUps.erase(this->powerUps.begin() + idx);
    }
    else{
        //remove object
        delete this->points[idx];
        this->points[idx] = nullptr;
        this->points.erase(this->points.begin() + idx);
    }
}

PowerUpObject* ObjectSpawner::generateRandomPowerUp()
{
    ObjectType random_type = static_cast<ObjectType>(rand() % LAST);

    switch (random_type)
    {
        case BATTERY_BOOST:
            return new OBJ_BatteryBoost();
            break;
        
        default:
            return new OBJ_BatteryBoost();
            break;
    }
}

void ObjectSpawner::spawnObject(SuperObject* object, TileManager* tilesManager, Entity* robot, bool is_powerUp)
{

    if(object == nullptr || tilesManager == nullptr || robot == nullptr)
    {
        throw GameException("Cannot spawn Object!!");
    }
    
    int width = tilesManager->gpInfo->maxScreenCol;
    int height = tilesManager->gpInfo->maxScreenRow;

    bool occupied = true;
    int row_idx = 0;
    int col_idx = 0;
    int object_x_left = 0;
    int object_y_top = 0;

    while(occupied)
    {
        row_idx = rand() % (height-1);
        col_idx = rand() % (width-1);

        //check if the tile has collision
        //if it is true, then the robot cannot access it (skip)
        int tile_number = tilesManager->getMap()[row_idx][col_idx];
        if(tilesManager->getTiles()[tile_number]->collision)
            continue;

        //Get Top Left Corner of the sprite
        object_x_left = col_idx * tilesManager->gpInfo->tileSize;
        object_y_top = row_idx * tilesManager->gpInfo->tileSize;

          
        object->setPosition(sf::Vector2f(object_x_left, object_y_top));

        //if object is where the robot is (skip)
        if(object->bounds.intersects(robot->getBounds()))
            continue;

        
        //Check if the position is valid for the existing objects
        //If the value is not valid then skip
        if(!this->checkObjectIntersection(object))
            continue;
        

        //after everything we can make sure it is not occupied
        occupied = false;
    }

    //Add object to the vector
    this->addObject(object, is_powerUp);
}

/**
 *          @return True if no intersection is made
 *                  False if there is an intersection
 * 
 *          This Method is to check if the new object intersects with the existing objects
 *          (PowerUps or Points)
 */
bool ObjectSpawner::checkObjectIntersection(SuperObject* object)
{
    //Check for the powerups objects
    for(int i=0; i < this->powerUps.size(); i++)
    {
        //If there is an intersection then the object is not in a valid position
        if(this->powerUps[i]->bounds.intersects(object->bounds))
        {
            return false;
        }
    }

    //Check for the points object
    for(int i=0; i < this->points.size(); i++)
    {
        //If there is an intersection then the object is not in a valid position
        if(this->points[i]->bounds.intersects(object->bounds))
        {
            return false;
        }
    }

    return true;
}

void ObjectSpawner::render(sf::RenderTarget* target)
{
    if(target == nullptr)
    {
        throw GameException("Error rendering Objects");
    }
    for(int i=0; i < current_powerUps; i++)
    {
        if(this->powerUps[i] != nullptr)
        {
            this->powerUps[i]->render(target);
        }
    }

    for(int i=0; i < this->points.size(); i++)
    {
        if(this->points[i] != nullptr)
        {
            this->points[i]->render(target);
        }
    }
}
