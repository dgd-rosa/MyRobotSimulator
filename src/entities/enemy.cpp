#include "entities/enemy.hpp"

Enemy::Enemy(float start_x, float start_y)
{
    this->sprite.setPosition(start_x, start_y);
    this->direction = DOWN;
    this->spriteCounter = 0;
    this->spriteNumber = 1;

    this->movementSpeed = 1.f;
    this->velocity = sf::Vector2f(0.f, this->movementSpeed);

    this->life_points = 3;

    this->initShape();
    this->initAttackTexture();
}

void Enemy::initShape()
{
    if(!this->right_texture1.loadFromFile("images/enemy/right1.png")){
        std::cout << "ERROR: Enemy texture not found!\n\n";
        return;
    }
    this->right_texture1.setSmooth(false);

    if(!this->right_texture2.loadFromFile("images/enemy/right2.png")){
        std::cout << "ERROR: Enemy texture not found!\n\n";
        return;
    }
    this->right_texture2.setSmooth(false);

    /*
        Left
    */
    if(!this->left_texture1.loadFromFile("images/enemy/left1.png")){
        std::cout << "ERROR: Enemy texture not found!\n\n";
        return;
    }
    this->left_texture1.setSmooth(false);

    if(!this->left_texture2.loadFromFile("images/enemy/left2.png")){
        std::cout << "ERROR: Enemy texture not found!\n\n";
        return;
    }
    this->left_texture2.setSmooth(false);


    this->sprite.setTexture(this->right_texture1);

    this->sprite.setScale(2, 2);



    sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();
    this->width_rect = 20;
    this->height_rect = 15;
    this->top_rect = this->height_rect/2;
    this->left_rect = this->width_rect/2;
    this->collisionRect.setSize(sf::Vector2f(spriteBounds.width-this->width_rect, spriteBounds.height-this->top_rect));
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+this->left_rect, spriteBounds.top+this->top_rect));
    this->collisionRect.setFillColor(sf::Color::Red);
}


void Enemy::initAttackTexture()
{
    if(!this->lightAttackTextureUp.loadFromFile("images/bullets/enemy_bullets/red_bullet_up.png"))
    {
        throw GameException("Could not load Red Projectile Texture");
    }
    
    this->lightAttackTextureUp.setSmooth(false);


    if(!this->lightAttackTextureDown.loadFromFile("images/bullets/enemy_bullets/red_bullet_down.png"))
    {
        throw GameException("Could not load Red Projectile Texture");
    }
    
    this->lightAttackTextureDown.setSmooth(false);


    if(!this->lightAttackTextureLeft.loadFromFile("images/bullets/enemy_bullets/red_bullet_left.png"))
    {
        throw GameException("Could not load Red Projectile Texture");
    }
    
    this->lightAttackTextureLeft.setSmooth(false);


    if(!this->lightAttackTextureRight.loadFromFile("images/bullets/enemy_bullets/red_bullet_right.png"))
    {
        throw GameException("Could not load Red Projectile Texture");
    }
    
    this->lightAttackTextureRight.setSmooth(false);
}

/**
 *      Check where the robot is and turn himself to the robot direction
 */
void Enemy::updateMovement(Robot* robot)
{
    auto robot_pos = robot->getPos();
    auto enemy_pos = this->getPos();

    auto robot_bounds = robot->getBounds();
    auto enemy_bounds = this->getBounds();

    //Turn Right
    if(robot_pos.x > enemy_pos.x)
    {
        this->facing_direction = RIGHT;
    }
    // Turn Left
    else{
        this->facing_direction = LEFT;
    }

    //move according the robot
    if(enemy_pos.y < robot_pos.y)
    {
        this->setVelocity(0.f, this->movementSpeed);
    }
    else if (enemy_pos.y > robot_pos.y){
        this->setVelocity(0.f, -this->movementSpeed);
    }
    else{
        this->setVelocity(0.f, 0.f);
    }

    this->sprite.move(this->velocity);
    //this->collisionRect.move(this->velocity);
    //Update CollisionRect
    sf::FloatRect spriteBounds = this->getBounds();
    sf::FloatRect rectBounds = this->collisionRect.getLocalBounds();
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+30/2, spriteBounds.top + spriteBounds.height - rectBounds.height));


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

bool Enemy::isFacingRobot(Robot* robot)
{
    auto robot_pos = robot->getPos();
    auto enemy_pos = this->getPos();

    sf::FloatRect bounds = this->getBounds();
    sf::FloatRect robot_bounds = robot->getBounds();

    if( (enemy_pos.y <= robot_pos.y + robot_bounds.height) && (enemy_pos.y + bounds.height >= robot_pos.y))
    {
        if(this->facing_direction == RIGHT)
        {
            chrono::time_point<chrono::steady_clock> now = chrono::steady_clock::now();
            if(robot_pos.x > enemy_pos.x){
            
                return true;
            }
        }
        else if(this->facing_direction == LEFT)
        {
            chrono::time_point<chrono::steady_clock> now = chrono::steady_clock::now();
            if(robot_pos.x < enemy_pos.x){
                return true;
            }
        }
    }

    return false;
}

/**
 *      Method to create a projectile with the right direction and texture
 */
Projectile* Enemy::createProjectileToShoot()
{
    switch (this->facing_direction)
    {
    case UP:
        return new Projectile(this->lightAttackTextureUp, this->facing_direction, this->getPos().x, this->getPos().y, 1.f, 1);
        break;
    case DOWN:
        return new Projectile(this->lightAttackTextureDown, this->facing_direction, this->getPos().x, this->getPos().y, 1.f, 1);
        break;
    case LEFT:
        std::cout << "Create Shot for left" << std::endl;
        return new Projectile(this->lightAttackTextureLeft, this->facing_direction, this->getPos().x, this->getPos().y, 1.f, 1);
        break;
    case RIGHT:
    std::cout << "Create Shot for right" << std::endl;
        return new Projectile(this->lightAttackTextureRight, this->facing_direction, this->getPos().x, this->getPos().y, 1.f, 1);
        break;
    }
}

Projectile* Enemy::shootToRobot(Robot* robot)
{
    auto robot_pos = robot->getPos();
    auto enemy_pos = this->getPos();

    sf::FloatRect bounds = this->getBounds();

    chrono::time_point<chrono::steady_clock> now = chrono::steady_clock::now();

    if(firstShot)
    {
        this->lastTimeShot = now - this->shoot_cooldown;
        this->firstShot = false;
    }
        

    if(now - this->lastTimeShot > this->shoot_cooldown)
    {
        if(this->isFacingRobot(robot))
        {
            //Robot for the first time facing Enemy
            if(!startedToWait)
            {
                this->time_robot_in_sight = now;
                startedToWait = true;
            }
            
            if(now - this->time_robot_in_sight > this->time_to_wait_before_shooting)
            {
                startedToWait = false;
                this->lastTimeShot = now;

                std::cout << "Create shot for Robot!!" << std::endl;
                
                return this->createProjectileToShoot();
            }
            
        }
        else{
            //Reset started to wait because the robot moved away
            if(startedToWait)
            {
                startedToWait = false;
            }
        }
    }
    return nullptr;
}

void Enemy::hitByProjectile(Projectile* projectile)
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
}

/**
 *      @return true if the enemy life points are 0 or below
 */
bool Enemy::isDead()
{
    return this->life_points <= 0;
}


void Enemy::update(Robot* robot)
{
    this->updateMovement(robot);
}

void Enemy::render(sf::RenderTarget* target)
{
    if(target==nullptr)
    {
        return;
    }

    switch(this->facing_direction)
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
    }

    target->draw(this->sprite);
}