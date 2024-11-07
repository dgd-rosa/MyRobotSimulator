#include "entities/robot.hpp"

void Robot::initVariables()
{
    this->direction = RIGHT;
    this->spriteCounter = 0;
    this->spriteNumber = 1;

    this->movementSpeed = 5.f;
    this->velocity = sf::Vector2f(0.f, 0.f);

    this->points = 0;
    this->battery = new Battery();
}

void Robot::initShape()
{
    if(!this->right_texture1.loadFromFile("images/robot/right1.png")){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->right_texture1.setSmooth(false);

    if(!this->right_texture2.loadFromFile("images/robot/right2.png")){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->right_texture2.setSmooth(false);

    /*
        Left
    */
    if(!this->left_texture1.loadFromFile("images/robot/left1.png")){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->left_texture1.setSmooth(false);

    if(!this->left_texture2.loadFromFile("images/robot/left2.png")){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->left_texture2.setSmooth(false);

    /*
        Down
    */
    if(!this->down_texture1.loadFromFile("images/robot/down1.png")){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->down_texture1.setSmooth(false);

    if(!this->down_texture2.loadFromFile("images/robot/down2.png")){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->down_texture2.setSmooth(false);

    /*
        UP
    */

    if(!this->up_texture1.loadFromFile("images/robot/up1.png")){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->up_texture1.setSmooth(false);

    if(!this->up_texture2.loadFromFile("images/robot/up2.png")){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->up_texture2.setSmooth(false);

    this->sprite.setTexture(this->right_texture1);

    this->sprite.setScale(2.5, 2.5);



    //Setup Collision Rectangle
    sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();

    this->top_rect = 24/2;
    this->left_rect = 30/2;
    this->collisionRect.setSize(sf::Vector2f(spriteBounds.width-30, spriteBounds.height-24));
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+30/2, spriteBounds.top+24/2));
    this->collisionRect.setFillColor(sf::Color::Red);
}


Robot::Robot(float start_x, float start_y){
    this->sprite.setPosition(start_x, start_y);

    this->initVariables();
    this->initShape();
}

Robot::~Robot(){
}

const sf::Vector2f & Robot::getPos() const
{
    return this->sprite.getPosition();
}

unsigned int Robot::getPoints()
{
    return this->points;
}

void Robot::updateInput()
{
    //Keyboard input
    //Left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->direction = LEFT;
        this->setVelocity(-this->movementSpeed, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->direction = RIGHT;
        this->setVelocity(this->movementSpeed, 0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->direction = UP;
        this->setVelocity(0, -this->movementSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->direction = DOWN;
        this->setVelocity(0, this->movementSpeed);
    }
    else{
        this->setVelocity(0, 0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->spriteCounter++;
        if(this->spriteCounter > 12)
        {
            if(this->spriteNumber == 1)
            {
                this->spriteNumber = 2;
            }
            else if(this->spriteNumber == 2)
            {
                this->spriteNumber = 1;
            }
            this->spriteCounter = 0;
        }
    }

    
}

void Robot::moveAfterCollision(sf::FloatRect myBounds, sf::FloatRect obstacleBounds, bool isDamaged)
{

    float overlapLeft = myBounds.left + myBounds.width - obstacleBounds.left;
    float overlapRight = obstacleBounds.left + obstacleBounds.width - myBounds.left;
    float overlapTop = myBounds.top + myBounds.height - obstacleBounds.top;
    float overlapBottom = obstacleBounds.top + obstacleBounds.height - myBounds.top;

    // Find the smallest overlap to prioritize
    bool resolveHorizontal = std::min(overlapLeft, overlapRight) < std::min(overlapTop, overlapBottom);

    float recoil = 0.f;
    if(isDamaged)
    {
        recoil = 30.f;
    }

    if(resolveHorizontal)
    {
        if(myBounds.left < obstacleBounds.left)
        {
            this->setPosition(obstacleBounds.left-myBounds.width-recoil, myBounds.top);
        }
        else if(myBounds.left > obstacleBounds.left)
        {
            this->setPosition(obstacleBounds.left+obstacleBounds.width+recoil, myBounds.top);
        }
    }
    else
    {
        if (myBounds.top < obstacleBounds.top)
        {
            this->setPosition(myBounds.left, obstacleBounds.top - myBounds.height-recoil); // Move up
        } 
        else if (myBounds.top > obstacleBounds.top)
        {
            this->setPosition(myBounds.left, obstacleBounds.top + obstacleBounds.height+recoil); // Move down
        }
    }
}

/*
    Update the sprite movement
 */
void Robot::updateMovement()
{
    this->sprite.move(this->velocity);

    //Update CollisionRect
    sf::FloatRect spriteBounds = this->getBounds();
    sf::FloatRect rectBounds = this->collisionRect.getLocalBounds();
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+30/2, spriteBounds.top + spriteBounds.height - rectBounds.height));
}



void Robot::checkObstacles(CollisionChecker* collisionChecker)
{
    if(collisionChecker->checkTile(this))
    {
        this->setVelocity(0.f, 0.f);
    }

    //Chekc PowerUps
    bool is_powerUp = true;
    int index = collisionChecker->checkObject(this, true, is_powerUp);

    //An object was picked up
    if(index != -1)
    {
        pickUpObject(index, collisionChecker->objSpawner->powerUps);
        //TODO: Check this the bool value
        collisionChecker->objSpawner->removeObject(index, is_powerUp);
    }
    

    is_powerUp = false; //change boolean to check points
    index = collisionChecker->checkObject(this, true, is_powerUp);
    //An object was picked up
    if(index != -1)
    {
        pickUpObject(index, collisionChecker->objSpawner->points);
        //TODO: Check this the bool value
        collisionChecker->objSpawner->removeObject(index, is_powerUp);
    }
}

void Robot::pickUpObject(int idx, std::vector<SuperObject*>& objs)
{
    if(idx != -1)
    {
        switch (objs[idx]->type)
        {
        case POWER_UP:
            this->pickUpPowerUp(dynamic_cast<PowerUpObject*>(objs[idx]));
            break;
        case POINTS:
            this->pickUpPoint(dynamic_cast<PointObject*>(objs[idx]));
            break;
        default:
            break;
        }
    }
}

void Robot::pickUpPowerUp(PowerUpObject* obj)
{
    switch (obj->powerUp_type)
    {
    case BATTERY_BOOST:
        this->battery->boost(30);
        break;
    
    default:
        break;
    }
}

void Robot::pickUpPoint(PointObject* obj)
{
    this->points += this->point_multiplier * obj->points;
}



void Robot::update(CollisionChecker* collisionChecker)
{
    this->updateInput();

    //Check Collision
    this->checkObstacles(collisionChecker);
    
    //Update Robot Movement
    this->updateMovement();

    this->battery->update();
}


void Robot::render(sf::RenderTarget* target){

    if(target == nullptr)
        return;
    

    switch(this->direction)
    {
        case RIGHT:
            if(this->spriteNumber == 1)
            {
                this->sprite.setTexture(this->right_texture1);
            }
            else if(this->spriteNumber == 2)
            {
                this->sprite.setTexture(this->right_texture2);
            }
            break;
        case LEFT:
            if(this->spriteNumber == 1)
            {
                this->sprite.setTexture(this->left_texture1);
            }
            else if(this->spriteNumber == 2)
            {
                this->sprite.setTexture(this->left_texture2);
            }
            break;
        case DOWN:
            if(this->spriteNumber == 1)
            {
                this->sprite.setTexture(this->down_texture1);
            }
            else if(this->spriteNumber == 2)
            {
                this->sprite.setTexture(this->down_texture2);
            }
            break;
        case UP:
            if(this->spriteNumber == 1)
            {
                this->sprite.setTexture(this->up_texture1);
            }
            else if(this->spriteNumber == 2)
            {
                this->sprite.setTexture(this->up_texture2);
            }
            break;
    }


    target->draw(this->sprite);

    this->battery->render(target);
}