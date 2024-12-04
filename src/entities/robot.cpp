#include "entities/robot.hpp"

void Robot::initVariables()
{
    this->direction = RIGHT;
    this->face_direction = RIGHT;
    this->spriteCounter = 0;
    this->spriteNumber = 1;

    this->velocity = sf::Vector2f(0.f, 0.f);

    this->points = 0;
    this->life_points = 6;
    this->battery = new Battery();

    this->point_multiplier = 1;
    this->level = 1;
    this->current_xp = 0;
}

void Robot::initConfigFile()
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

    this->movementSpeed = config["Robot"]["speed"];
    this->life_points = config["Robot"]["lifePoints"];
    this->xp_for_next_level = config["Robot"]["xp_for_next_level"];
    this->xp_multiplier = config["Robot"]["xp_multiplier"];

    int cooldown = config["Robot"]["ligthAttackCooldown"];
    this->light_attack_cooldown = std::chrono::milliseconds(cooldown);
    this->light_attack_speed = config["Robot"]["lightAttackSpeed"];
    this->light_attack_damage = config["Robot"]["lightAttackDamage"];


    this->right1TexturePath = config["Robot"]["right1Path"];
    this->right2TexturePath = config["Robot"]["right2Path"];
    this->left1TexturePath = config["Robot"]["left1Path"];
    this->left2TexturePath = config["Robot"]["left2Path"];
    this->up1TexturePath = config["Robot"]["up1Path"];
    this->up2TexturePath = config["Robot"]["up2Path"];
    this->down1TexturePath = config["Robot"]["down1Path"];
    this->down2TexturePath = config["Robot"]["down2Path"];


    this->lightAttackUpPath = config["Robot"]["lightAttackUpPath"];
    this->lightAttackDownPath = config["Robot"]["lightAttackDownPath"];
    this->lightAttackLeftPath = config["Robot"]["lightAttackLeftPath"];
    this->lightAttackRightPath = config["Robot"]["lightAttackRightPath"];

}

void Robot::initShape()
{
    if(!this->right_texture1.loadFromFile(this->right1TexturePath)){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->right_texture1.setSmooth(false);

    if(!this->right_texture2.loadFromFile(this->right2TexturePath)){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->right_texture2.setSmooth(false);

    /*
        Left
    */
    if(!this->left_texture1.loadFromFile(this->left1TexturePath)){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->left_texture1.setSmooth(false);

    if(!this->left_texture2.loadFromFile(this->left2TexturePath)){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->left_texture2.setSmooth(false);

    /*
        Down
    */
    if(!this->down_texture1.loadFromFile(this->down1TexturePath)){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->down_texture1.setSmooth(false);

    if(!this->down_texture2.loadFromFile(this->down2TexturePath)){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->down_texture2.setSmooth(false);

    /*
        UP
    */

    if(!this->up_texture1.loadFromFile(this->up1TexturePath)){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->up_texture1.setSmooth(false);

    if(!this->up_texture2.loadFromFile(this->up2TexturePath)){
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

Robot::Robot(float start_x, float start_y, std::shared_ptr<SoundManager> soundManager){
    this->soundManager = soundManager;
    this->sprite.setPosition(start_x, start_y);
    this->initConfigFile();
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

unsigned int Robot::getLevel()
{
    return this->level;
}

void Robot::updateInput()
{
    //Keyboard input
    //Left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->direction = LEFT;
        this->face_direction = LEFT;
        this->setVelocity(-this->movementSpeed, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        this->direction = RIGHT;
        this->face_direction = RIGHT;
        this->setVelocity(this->movementSpeed, 0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->direction = UP;
        this->face_direction = UP;
        this->setVelocity(0, -this->movementSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        this->direction = DOWN;
        this->face_direction = DOWN;
        this->setVelocity(0, this->movementSpeed);
    }
    else{
        this->setVelocity(0, 0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
       sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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

void Robot::moveAfterCollision(Entity* entity)
{

    sf::FloatRect myBounds = this->getBounds();
    sf::FloatRect obstacleBounds = entity->getBounds();
    float overlapLeft = myBounds.left + myBounds.width - obstacleBounds.left;
    float overlapRight = obstacleBounds.left + obstacleBounds.width - myBounds.left;
    float overlapTop = myBounds.top + myBounds.height - obstacleBounds.top;
    float overlapBottom = obstacleBounds.top + obstacleBounds.height - myBounds.top;

    // Find the smallest overlap to prioritize
    bool resolveHorizontal = std::min(overlapLeft, overlapRight) < std::min(overlapTop, overlapBottom);

    float recoil = 20.f;
    
    auto myVel = this->getVelocity();

    float recoilVel = 30.f;
    if(resolveHorizontal)
    {
        if(myBounds.left < obstacleBounds.left)
        {
            //this->setPosition(obstacleBounds.left-myBounds.width-recoil, myBounds.top);
            this->direction = LEFT;
            this->setVelocity(-recoilVel, 0.f);
        }
        else if(myBounds.left > obstacleBounds.left)
        {
            //this->setPosition(obstacleBounds.left+obstacleBounds.width+recoil, myBounds.top);
            this->direction = RIGHT;
            this->setVelocity(recoilVel, 0.f);
        }
    }
    else
    {
        if (myBounds.top < obstacleBounds.top)
        {
            //this->setPosition(myBounds.left, obstacleBounds.top - myBounds.height-recoil); // Move up
            this->direction = UP;
            this->setVelocity(0.f, -recoilVel);
        } 
        else if (myBounds.top > obstacleBounds.top)
        {
            //this->setPosition(myBounds.left, obstacleBounds.top + obstacleBounds.height+recoil); // Move down
            this->direction = DOWN;
            this->setVelocity(0.f, recoilVel);
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
        //Check if Sound Managers still exists (robot only has a weak ptr pointing to sound manager)
        if (auto real_sound_manager = this->soundManager.lock()) {
            real_sound_manager->playSound("pick_boost");
        }
        
        this->pickUpPowerUp(dynamic_cast<PowerUpObject*>(obj));
        break;
    case POINTS:
        
        //Check if Sound Managers still exists (robot only has a weak ptr pointing to sound manager)
        if (auto real_sound_manager = this->soundManager.lock()) {
            real_sound_manager->playSound("pick_screw");
        }
        this->pickUpPoint(dynamic_cast<PointObject*>(obj));
        break;
    default:
        break;
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
    this->current_xp += this->point_multiplier * obj->points;
}

void Robot::updateXP()
{
    if(this->current_xp >= this->xp_for_next_level)
    {
        //Level UPPPP
        this->xp_for_next_level = this->xp_for_next_level * 2;
        this->level++;
        std::cout << "Level UPPPPP!! XP for level " << this->level + 1 << std::endl;
    }
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
    //Check if Sound Managers still exists (robot only has a weak ptr pointing to sound manager)
    if (auto real_sound_manager = this->soundManager.lock()) {
        real_sound_manager->playSound("hit");
    }
}


void Robot::hitEntity(Entity* entity)
{
    if(entity == nullptr)
        return;

    this->moveAfterCollision(entity);

    if(auto real_sound_manager = this->soundManager.lock())
    {
        real_sound_manager->playSound("hit");
    }
}

Projectile* Robot::lightAttack()
{
    chrono::time_point<chrono::steady_clock> now = chrono::steady_clock::now();

    if(firstShot)
    {
        this->lastTimeShot = now - this->light_attack_cooldown;
        this->firstShot = false;
    }

    if(now - this->lastTimeShot > this->light_attack_cooldown)
    {
        //Check if Sound Managers still exists (robot only has a weak ptr pointing to sound manager)
        if (auto real_sound_manager = this->soundManager.lock()) {
            real_sound_manager->playSound("light_attack");
        }
        this->lastTimeShot = now;
        switch (this->face_direction)
        {
        case UP:
            return new Projectile(this->lightAttackTextureUp, this->face_direction, this->getPos().x, this->getPos().y, this->light_attack_speed, this->light_attack_damage);
            break;
        case DOWN:
            return new Projectile(this->lightAttackTextureDown, this->face_direction, this->getPos().x, this->getPos().y, this->light_attack_speed, this->light_attack_damage);
            break;
        case LEFT:
            return new Projectile(this->lightAttackTextureLeft, this->face_direction, this->getPos().x, this->getPos().y, this->light_attack_speed, this->light_attack_damage);
            break;
        case RIGHT:
            return new Projectile(this->lightAttackTextureRight, this->face_direction, this->getPos().x, this->getPos().y, this->light_attack_speed, this->light_attack_damage);
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

    this->updateXP();
}


void Robot::render(sf::RenderTarget* target){

    if(target == nullptr)
        return;
    

    switch(this->face_direction)
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