#include "entities/robot.hpp"

void Robot::initVariables()
{
    this->direction = RIGHT;
    this->spriteCounter = 0;
    this->spriteNumber = 1;

    this->movementSpeed = 5.f;
    this->velocity = sf::Vector2f(0.f, 0.f);

    this->points = 0;
    this->life_points = 6;
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

void Robot::initAttackTexture()
{
    if(!this->lightAttackTextureUp.loadFromFile("images/bullets/robot_bullets/blue_bullet_up.png"))
    {
        throw GameException("Could not load Red Projectile Texture");
    }
    
    this->lightAttackTextureUp.setSmooth(false);


    if(!this->lightAttackTextureDown.loadFromFile("images/bullets/robot_bullets/blue_bullet_down.png"))
    {
        throw GameException("Could not load Red Projectile Texture");
    }
    
    this->lightAttackTextureDown.setSmooth(false);


    if(!this->lightAttackTextureLeft.loadFromFile("images/bullets/robot_bullets/blue_bullet_left.png"))
    {
        throw GameException("Could not load Red Projectile Texture");
    }
    
    this->lightAttackTextureLeft.setSmooth(false);


    if(!this->lightAttackTextureRight.loadFromFile("images/bullets/robot_bullets/blue_bullet_right.png"))
    {
        throw GameException("Could not load Red Projectile Texture");
    }
    
    this->lightAttackTextureRight.setSmooth(false);
}

Robot::Robot(float start_x, float start_y){
    this->sprite.setPosition(start_x, start_y);
    this->initVariables();
    this->initShape();
    this->initAttackTexture();
}

Robot::~Robot()
{
}

unsigned int Robot::getPoints()
{
    return this->points;
}

unsigned int Robot::getBatteryValue()
{
    return this->battery->battery;
}

unsigned int Robot::getLifePoints()
{
    return this->life_points;
}

void Robot::updateInput()
{
    //Keyboard input
    //Left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->direction = LEFT;
        this->setVelocity(-this->movementSpeed, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        this->direction = RIGHT;
        this->setVelocity(this->movementSpeed, 0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->direction = UP;
        this->setVelocity(0, -this->movementSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
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

Projectile* Robot::shoot()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        return this->lightAttack();
    }
    else{
        return nullptr;
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


void Robot::pickUpObject(SuperObject* obj)
{
    switch (obj->type)
    {
    case POWER_UP:
        this->pickUpPowerUp(dynamic_cast<PowerUpObject*>(obj));
        break;
    case POINTS:
        this->pickUpPoint(dynamic_cast<PointObject*>(obj));
        break;
    default:
        break;
    }
    
}

void Robot::pickUpPowerUp(PowerUpObject* obj)
{
    std::cout << "Pick Up PowerUp" << std::endl;
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


void Robot::obstacleCollision()
{
    this->setVelocity(0.f, 0.f);
}

void Robot::hitByProjectile(Projectile* projectile)
{
    if(projectile == nullptr)
        return;

    if(this->life_points < projectile->damage)
    {
        this->life_points = 0;
    }
    else
    {
        this->life_points -= projectile->damage;
    }
    std::cout << "Hit by projectile! Current Life points: " << this->life_points << std::endl;
}

Projectile* Robot::lightAttack()
{
    chrono::time_point<chrono::steady_clock> now = chrono::steady_clock::now();

    if(firstShot)
    {
        this->lastTimeShot = now - this->shoot_cooldown;
        this->firstShot = false;
    }

    if(now - this->lastTimeShot > this->shoot_cooldown)
    {
        this->lastTimeShot = now;
        switch (this->direction)
        {
        case UP:
            return new Projectile(this->lightAttackTextureUp, this->direction, this->getPos().x, this->getPos().y, 2.f, 2);
            break;
        case DOWN:
            return new Projectile(this->lightAttackTextureDown, this->direction, this->getPos().x, this->getPos().y, 2.f, 2);
            break;
        case LEFT:
            return new Projectile(this->lightAttackTextureLeft, this->direction, this->getPos().x, this->getPos().y, 2.f, 2);
            break;
        case RIGHT:
            return new Projectile(this->lightAttackTextureRight, this->direction, this->getPos().x, this->getPos().y, 2.f, 2);
            break;
        }
    }
    else{
        return nullptr;
    }
}

void Robot::update()
{   
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