#include "objects/object_spawner.hpp"

ObjectSpawner::ObjectSpawner(TileManager* tilesManager)
{
    this->tilesManager = tilesManager;
    this->initConfigFile();
}

void ObjectSpawner::initConfigFile()
{
    // Open the JSON file
    std::ifstream file("config.json");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config.json" << std::endl;
        return;
    }

    // Parse the JSON file
    json config;
    try {
        file >> config;
    } catch (const json::parse_error& e) {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
        return;
    }

    try{
        int screwCooldown = config["ObjectSpawner"]["screw_cooldown"];
        this->screw_spawn_cooldown = std::chrono::milliseconds(screwCooldown);
        int powerUpCooldown = config["ObjectSpawner"]["powerup_cooldown"];
        this->powerup_spawn_cooldown = std::chrono::milliseconds(powerUpCooldown);

        this->max_number_powerUps = config["ObjectSpawner"]["max_number_powerups"];
        this->max_number_screws = config["ObjectSpawner"]["max_number_screws"];
    }
    catch(const std::exception& e)
    {
        throw GameException("Could not load Object Spawner values from config file");
    }
    
}

void ObjectSpawner::update(TileManager* tilesManager, Entity* robot)
{
    auto now = std::chrono::steady_clock::now();

    //Points UPDATE
    if(now - this->lastTimeUpdate_points > this->screw_spawn_cooldown)
    {
        this->lastTimeUpdate_points = now;

        if(this->points.size() < this->max_number_screws)
        {
            //Generate Random Power Up -> chooses a random power up from the enum
            this->spawnObject(new OBJ_Screw(), robot, false);
        }
    }
    
    
    //POWER UPS Update
    if(now - this->lastTimeUpdate_powerups > this->powerup_spawn_cooldown)
    {
        this->lastTimeUpdate_powerups = now;
        if(this->powerUps.size() < this->max_number_powerUps)
        {
            //Generate Random Power Up -> chooses a random power up from the enum
            this->spawnObject(this->generateRandomPowerUp(), robot, true);
        }
    }
}

void ObjectSpawner::addObject(SuperObject* object, bool powerUp)
{
    if(powerUp)
    {
        this->powerUps.push_back(object);
    }
    else{
        this->points.push_back(object);
    }
}

void ObjectSpawner::removeObject(int idx, bool powerUp)
{
    if(powerUp)
    {
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
        
        case LIFE_BOOST:{
            OBJ_Heart* heart = new OBJ_Heart();
            heart->setHeartTexture("full");
            return heart;
            break;
        }
        default:
            return new OBJ_BatteryBoost();
            break;
    }
}

void ObjectSpawner::spawnRandomPowerUp(int pos_x, int pos_y)
{
    PowerUpObject* new_obj = this->generateRandomPowerUp();
    new_obj->setPosition(sf::Vector2f(pos_x, pos_y));

    //Get Top Left Corner of the sprite
    int col_idx = pos_x / tilesManager->gpInfo->tileSize;
    int width_idx = pos_y / tilesManager->gpInfo->tileSize;

    //If it is in a wall
    int tileNumber = tilesManager->getMap()[width_idx][col_idx];
    if(tilesManager->getTiles()[tileNumber]->collision)
    {
        return;
    }

    for(auto obj : this->powerUps)
    {
        if(obj->getBounds().intersects(new_obj->getBounds()))
        {
            return;
        }
    }

    for(auto obj : this->points)
    {
        if(obj->getBounds().intersects(new_obj->getBounds()))
        {
            return;
        }
    }

    this->addObject(new_obj, true);
}

void ObjectSpawner::spawnObject(SuperObject* object, Entity* robot, bool is_powerUp)
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
    for(int i=0; i < this->powerUps.size(); i++)
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
