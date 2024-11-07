#include "CollisionChecker.hpp"

CollisionChecker::CollisionChecker(GamePanelInfo* gpInfo, TileManager* tileManager, ObjectSpawner* objSpawner)
{
    this->gpInfo = gpInfo;
    this->tileManager = tileManager;
    this->objSpawner = objSpawner;
}

bool CollisionChecker::checkTile(Entity* entity)
{
    if(entity == nullptr)
        throw GameException("Checktile: Entity pointer is null");
        
    sf::FloatRect entityCollisionBounds = entity->collisionRect.getGlobalBounds();

    int entityLeftWorldX = entityCollisionBounds.left;
    int entityRightWorldX = entityCollisionBounds.left + entityCollisionBounds.width;
    int entityTopWorldY = entityCollisionBounds.top;
    int entityBottomWorldY = entityCollisionBounds.top + entityCollisionBounds.height;

    /*
    * This entity values are the values of the indexes of the map grid
    of the 4 tiles that 
    */
    //Find Column
    int entityLeftCol = entityLeftWorldX/this->gpInfo->tileSize;
    int entityRightCol = entityRightWorldX/this->gpInfo->tileSize;
    
    //Find Rows
    int entityTopRow = entityTopWorldY/this->gpInfo->tileSize;
    int entityBottomRow = entityBottomWorldY/this->gpInfo->tileSize;


    std::vector<std::vector<int>> map = this->tileManager->getMap();
    std::vector<GameTile*> tiles = this->tileManager->getTiles();

    sf::Vector2f velocity = entity->getVelocity();


    switch (entity->direction)
    {
        case UP:
        {
            entityTopRow = (entityTopWorldY + velocity.y)/this->gpInfo->tileSize;
            
            if(entityTopRow < 0 ||
                entityBottomRow >= this->gpInfo->maxScreenRow ||
                entityLeftCol < 0 ||
                entityRightCol >= this->gpInfo->maxScreenCol)
                {
                    std::cout << "Out of the window" << std::endl;
                    return false;
                }

            return this->checkTileLine(entityLeftCol, entityRightCol, entityTopRow, true);

            break;
        }
        case DOWN:
        {
            entityBottomRow = (entityBottomWorldY + velocity.y)/this->gpInfo->tileSize;

            if(entityTopRow < 0 ||
                entityBottomRow >= this->gpInfo->maxScreenRow ||
                entityLeftCol < 0 ||
                entityRightCol >= this->gpInfo->maxScreenCol)
            {
                std::cout << "Out of the window" << std::endl;
                return false;
            }
            return this->checkTileLine(entityLeftCol, entityRightCol, entityBottomRow, true);
            break;
        }
        case LEFT:
        {
            entityLeftCol = (entityLeftWorldX + velocity.x)/this->gpInfo->tileSize;

            if(entityTopRow < 0 ||
                entityBottomRow >= this->gpInfo->maxScreenRow ||
                entityLeftCol < 0 ||
                entityRightCol >= this->gpInfo->maxScreenCol)
            {
                std::cout << "Out of the window" << std::endl;
                return false;
            }
            return this->checkTileLine(entityTopRow, entityBottomRow, entityLeftCol, false);
            break;
        }
        case RIGHT:
        {
            entityRightCol = (entityRightWorldX + velocity.x)/this->gpInfo->tileSize;
            
            if(entityTopRow < 0 ||
                entityBottomRow >= this->gpInfo->maxScreenRow ||
                entityLeftCol < 0 ||
                entityRightCol >= this->gpInfo->maxScreenCol)
            {
                std::cout << "Out of the window" << std::endl;
                return false;
            }
            return this->checkTileLine(entityTopRow, entityBottomRow, entityRightCol, false);
            break;
        }
        default:
            break;
    }

    return false;

}


/**
 *  CheckTileLine:
 * 
 *      Method to check if there are any obstacles between 2 indexes of the map with a
 *      stable index.
 *      
 *      - Bool horizontal chooses if the it is to check a row or a column of the map
 *      - This is need in case the Entity is larger than the tiles
 */

bool CollisionChecker::checkTileLine(int low_idx, int high_idx, int stable_idx, bool horizontal)

{
    int tilenumber;
    for(int i=low_idx; i <= high_idx; i++)
    {
        if(horizontal)
        {
            // Horizontal checking stable index on the row
            tilenumber = this->tileManager->getMap()[stable_idx][i];
        }
        else
        {
            // Horizontal checking: stable index on the column
            tilenumber = this->tileManager->getMap()[i][stable_idx];
        }

        if(this->tileManager->getTiles()[tilenumber]->collision == true)
        {
            return true;
        }
    }

    return false;
}

bool CollisionChecker::checkWindowCollision(Entity* entity)
{
    bool collision = false;
    //Left Bound
    if(entity->getBounds().left < 0.f)
    {
        collision = true;
        entity->setPosition(0.f, entity->getBounds().top);
        std::cout << "Window Collision!!" << std::endl;
    }
    //Right bound
    else if(entity->getBounds().left + entity->getBounds().width > this->tileManager->gpInfo->screenWidth)
    {
        collision = true;
        entity->setPosition(this->tileManager->gpInfo->screenWidth - entity->getBounds().width, entity->getBounds().top);
        std::cout << "Window Collision!!" << std::endl;
    }
    
    //Top Bound
    if(entity->getBounds().top < 0.f)
    {
        collision = true;
        entity->setPosition(entity->getBounds().left, 0.f);
        std::cout << "Window Collision!!" << std::endl;
    }
    //Bottom Bound
    else if(entity->getBounds().top + entity->getBounds().height > this->tileManager->gpInfo->screenHeight)
    {
        collision = true;
        entity->setPosition(entity->getBounds().left, this->tileManager->gpInfo->screenHeight - entity->getBounds().height);
        std::cout << "Window Collision!!" << std::endl;
    }

    return collision;
}


int CollisionChecker::checkObject(Entity* entity, bool player, bool is_powerUp)
{
    int index = -1;

    if(entity == nullptr)
    {
        throw GameException("Check Object with null entity");
    }

    //Check For PowerUps
    if(is_powerUp)
    {
        for(int i=0; i < this->objSpawner->current_powerUps; i++)
        {
            if(this->objSpawner->powerUps[i] != nullptr)
            {
                //Intersected
                if(this->objSpawner->powerUps[i]->bounds.intersects(entity->getBounds()))
                {
                    if(player)
                    {
                        index = i;
                    }
                    break;
                }
            }
        }    
    }
    else
    {
        //Check For Points
        for(int i=0; i < this->objSpawner->points.size(); i++)
        {
            if(this->objSpawner->points[i] != nullptr)
            {
                //Intersected
                if(this->objSpawner->points[i]->bounds.intersects(entity->getBounds()))
                {
                    std::cout << "Intersected" << endl;
                    if(player)
                    {
                        index = i;
                    }
                    break;
                }
            }
        }
    }

    return index;
}

