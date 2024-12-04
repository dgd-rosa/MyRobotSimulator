#include "entities/enemy.hpp"

Enemy::Enemy(float start_x, float start_y, std::weak_ptr<SoundManager> soundManager)
{
    this->sprite.setPosition(start_x, start_y);
    this->direction = DOWN;
    this->spriteCounter = 0;
    this->dyingCounter = 0;
    this->spriteNumber = 1;
    this->movementSpeed = 0.f;
    this->velocity = sf::Vector2f(0.f, this->movementSpeed);

    this->soundManager = soundManager;

    this->initConfigFile();
    this->initShape();
    this->initAttackTexture();
}

void Enemy::initConfigFile()
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

    this->movementSpeed = config["Enemy"]["speed"];
    this->life_points = config["Enemy"]["lifePoints"];
    int cooldown = config["Robot"]["ligthAttackCooldown"];
    this->light_attack_cooldown = std::chrono::milliseconds(cooldown);
    this->light_attack_speed = config["Robot"]["lightAttackSpeed"];
    this->light_attack_damage = config["Robot"]["lightAttackDamage"];

    this->right1TexturePath = config["Enemy"]["right1Path"];
    this->right2TexturePath = config["Enemy"]["right2Path"];
    this->left1TexturePath = config["Enemy"]["left1Path"];
    this->left2TexturePath = config["Enemy"]["left2Path"];

    this->lightAttackUpPath = config["Enemy"]["lightAttackUpPath"];
    this->lightAttackDownPath = config["Enemy"]["lightAttackDownPath"];
    this->lightAttackLeftPath = config["Enemy"]["lightAttackLeftPath"];
    this->lightAttackRightPath = config["Enemy"]["lightAttackRightPath"];


}

void Enemy::initShape()
{
    if(!this->right_texture1.loadFromFile(this->right1TexturePath)){
        std::cout << "ERROR: Enemy texture not found!\n\n";
        return;
    }
    this->right_texture1.setSmooth(false);

    if(!this->right_texture2.loadFromFile(this->right2TexturePath)){
        std::cout << "ERROR: Enemy texture not found!\n\n";
        return;
    }
    this->right_texture2.setSmooth(false);

    /*
        Left
    */
    if(!this->left_texture1.loadFromFile(this->left1TexturePath)){
        std::cout << "ERROR: Enemy texture not found!\n\n";
        return;
    }
    this->left_texture1.setSmooth(false);

    if(!this->left_texture2.loadFromFile(this->left2TexturePath)){
        std::cout << "ERROR: Enemy texture not found!\n\n";
        return;
    }
    this->left_texture2.setSmooth(false);


    this->sprite.setTexture(this->right_texture1);

    this->sprite.setScale(2, 2);



    sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();
    this->width_rect = 20;
    this->height_rect = 20;
    this->top_rect = this->height_rect/2;
    this->left_rect = this->width_rect/2;


    this->collisionRect.setSize(sf::Vector2f(spriteBounds.width-this->width_rect, spriteBounds.height-this->height_rect));
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+this->left_rect, spriteBounds.top+spriteBounds.height-this->collisionRect.getGlobalBounds().height));
    this->collisionRect.setFillColor(sf::Color::Red);
}


void Enemy::initAttackTexture()
{
    if(!this->lightAttackTextureUp.loadFromFile(this->lightAttackUpPath))
    {
        throw GameException("Could not load Red Projectile Texture");
    }
    
    this->lightAttackTextureUp.setSmooth(false);


    if(!this->lightAttackTextureDown.loadFromFile(this->lightAttackDownPath))
    {
        throw GameException("Could not load Red Projectile Texture");
    }
    
    this->lightAttackTextureDown.setSmooth(false);


    if(!this->lightAttackTextureLeft.loadFromFile(this->lightAttackLeftPath))
    {
        throw GameException("Could not load Red Projectile Texture");
    }
    
    this->lightAttackTextureLeft.setSmooth(false);


    if(!this->lightAttackTextureRight.loadFromFile(this->lightAttackRightPath))
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
    if((enemy_pos.y < robot_pos.y && enemy_pos.y + enemy_bounds.height < robot_pos.y + robot_bounds.height))
    {
        this->setVelocity(0.f, this->movementSpeed);
        this->direction = DOWN;
    }
    else if ((enemy_pos.y > robot_pos.y && enemy_pos.y + enemy_bounds.height > robot_pos.y + robot_bounds.height)){
        this->setVelocity(0.f, -this->movementSpeed);
        this->direction = UP;
    }
    else{
        this->setVelocity(0.f, 0.f);
    }

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

void Enemy::dyingAnimation()
{
    this->dyingCounter++;

    int i = 10;

    sf::Color spriteColor = sprite.getColor(); // Get current color
    if(dyingCounter > 0 && dyingCounter <= i)
    {
        spriteColor.a = 0.f; // Set alpha to 50% transparency
        sprite.setColor(spriteColor);
    }
    else if(dyingCounter > i && dyingCounter <= i*2)
    {
        spriteColor.a = 255.0f; // Set alpha to 50% transparency
        sprite.setColor(spriteColor);
    }
    else if(dyingCounter > i*2 && dyingCounter <= i*3)
    {
        spriteColor.a = 0.f; // Set alpha to 50% transparency
        sprite.setColor(spriteColor);
    }
    else if(dyingCounter > i*3 && dyingCounter <= i*4)
    {
        spriteColor.a = 255.0f; // Set alpha to 50% transparency
        sprite.setColor(spriteColor);
    }
    else
    {
        this->dyingCounter = 0;
        this->alive = false;
        this->dying = false;
    }
}

void Enemy::moveEnemy()
{
    this->sprite.move(this->velocity);

    //Update CollisionRect
    sf::FloatRect spriteBounds = this->getBounds();
    sf::FloatRect rectBounds = this->collisionRect.getLocalBounds();
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+this->left_rect, spriteBounds.top + spriteBounds.height - rectBounds.height));
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
        return new Projectile(this->lightAttackTextureUp, this->facing_direction, this->getPos().x, this->getPos().y, this->light_attack_speed, 1);
        break;
    case DOWN:
        return new Projectile(this->lightAttackTextureDown, this->facing_direction, this->getPos().x, this->getPos().y, this->light_attack_speed, 1);
        break;
    case LEFT:
        return new Projectile(this->lightAttackTextureLeft, this->facing_direction, this->getPos().x, this->getPos().y, this->light_attack_speed, 1);
        break;
    case RIGHT:
        return new Projectile(this->lightAttackTextureRight, this->facing_direction, this->getPos().x, this->getPos().y, this->light_attack_speed, 1);
        break;
    }
}

Projectile* Enemy::shootToRobot(Robot* robot)
{
    auto robot_pos = robot->getPos();
    auto enemy_pos = this->getPos();

    sf::FloatRect bounds = this->getBounds();

    chrono::time_point<chrono::steady_clock> now = chrono::steady_clock::now();

    
        

    if(this->dying == false && this->alive == true)
    {
        if(firstShot)
        {
            this->lastTimeShot = now - this->light_attack_cooldown;
            this->firstShot = false;
        }

        if(now - this->lastTimeShot > this->light_attack_cooldown)
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

    //Check if Sound Managers still exists
    if (auto sp = this->soundManager.lock()) {
        sp->playSound("hit");
    } else {
        // sp no longer exists!
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
    if(this->dying == true)
    {
        this->dyingAnimation();
        this->setVelocity(0.f,0.f);
    }
    else{
        this->updateMovement(robot);
    }
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

            if(!this->dying)
            {
                if(this->spriteNumber == 1)
                {
                    this->sprite.setTexture(this->right_texture1);
                }
                else if(this->spriteNumber == 2)
                {
                    this->sprite.setTexture(this->right_texture2);
                }
            }
            break;
        case LEFT:
            if(!this->dying)
            {
                if(this->spriteNumber == 1)
                {
                    this->sprite.setTexture(this->left_texture1);
                }
                else if(this->spriteNumber == 2)
                {
                    this->sprite.setTexture(this->left_texture2);
                }    
            }
            
            break;
    }

    target->draw(this->sprite);
}