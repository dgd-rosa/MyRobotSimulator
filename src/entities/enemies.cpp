#include "entities/enemy.hpp"

///////////////////////// Enemy Weak ///////////////////////////

EnemyWeak::EnemyWeak(float start_x, float start_y, std::weak_ptr<SoundManager> soundManager)
{
    enemyType = WEAK;
    this->sprite.setPosition(start_x, start_y);
    this->direction = DOWN;
    this->spriteCounter = 0;
    this->dyingCounter = 0;
    this->damagedCounter = 0;
    this->spriteNumber = 1;
    this->movementSpeed = 0.f;
    this->velocity = sf::Vector2f(0.f, this->movementSpeed);

    this->soundManager = soundManager;

    this->initConfigFile();
    this->initShape();
    this->initAttackTexture();

    this->setDirectionVelocity(RIGHT, this->movementSpeed);

    this->healthBar = std::make_unique<HealthBar>(30.f, 6.f, this->max_life);
}

void EnemyWeak::initConfigFile()
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

    this->movementSpeed = config["Enemy"]["Weak"]["speed"];
    this->life_points = config["Enemy"]["Weak"]["lifePoints"];
    this->max_life = life_points;
    int cooldown = config["Enemy"]["Weak"]["directionResetCooldown"];
    this->directionResetCooldown = std::chrono::milliseconds(cooldown);
    this->xp_points = config["Enemy"]["Weak"]["xp_points"];


    cooldown = config["Enemy"]["Weak"]["ligthAttackCooldown"];
    this->light_attack_cooldown = std::chrono::milliseconds(cooldown);
    this->light_attack_speed = config["Enemy"]["Weak"]["lightAttackSpeed"];
    this->light_attack_damage = config["Enemy"]["Weak"]["lightAttackDamage"];

    this->right1TexturePath = config["Enemy"]["Weak"]["right1Path"];
    this->right2TexturePath = config["Enemy"]["Weak"]["right2Path"];
    this->left1TexturePath = config["Enemy"]["Weak"]["left1Path"];
    this->left2TexturePath = config["Enemy"]["Weak"]["left2Path"];

    this->lightAttackUpPath = config["Enemy"]["Weak"]["lightAttackUpPath"];
    this->lightAttackDownPath = config["Enemy"]["Weak"]["lightAttackDownPath"];
    this->lightAttackLeftPath = config["Enemy"]["Weak"]["lightAttackLeftPath"];
    this->lightAttackRightPath = config["Enemy"]["Weak"]["lightAttackRightPath"];
}

void EnemyWeak::initShape()
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
    this->realColor = this->sprite.getColor();



    sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();
    this->width_rect = 20;
    this->height_rect = 20;
    this->top_rect = this->height_rect/2;
    this->left_rect = this->width_rect/2;


    this->collisionRect.setSize(sf::Vector2f(spriteBounds.width-this->width_rect, spriteBounds.height-this->height_rect));
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+this->left_rect, spriteBounds.top+spriteBounds.height-this->collisionRect.getGlobalBounds().height));
    this->collisionRect.setFillColor(sf::Color::Red);

}

/**
 *  Weak enemy moves randomly without knowing the robot position
 */
void EnemyWeak::updateMovement(Robot* robot)
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

    auto now = chrono::steady_clock::now();
    if(now - this->lastTimeChangeDirections > this->directionResetCooldown)
    {
        Direction random_direction = static_cast<Direction>(rand() % 4);
        this->direction = random_direction;
        
        if(this->direction == RIGHT)
        {
            this->facing_direction = RIGHT;
        }
        else if(this->direction == LEFT)
        {
            this->facing_direction = LEFT;
        }

        this->setDirectionVelocity(this->direction, this->movementSpeed);
        this->lastTimeChangeDirections = now;
    }
    
}

///////////////////////// Enemy Medium ///////////////////////////

EnemyMedium::EnemyMedium(float start_x, float start_y, std::weak_ptr<SoundManager> soundManager)
{
    enemyType = MEDIUM;
    this->sprite.setPosition(start_x, start_y);
    this->direction = DOWN;
    this->spriteCounter = 0;
    this->dyingCounter = 0;
    this->damagedCounter = 0;
    this->spriteNumber = 1;
    this->movementSpeed = 0.f;
    this->velocity = sf::Vector2f(0.f, this->movementSpeed);

    this->soundManager = soundManager;

    this->initConfigFile();
    this->initShape();
    this->initAttackTexture();

    this->healthBar = std::make_unique<HealthBar>(30.f, 6.f, this->max_life);
}


void EnemyMedium::initConfigFile()
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

    this->movementSpeed = config["Enemy"]["Medium"]["speed"];
    this->life_points = config["Enemy"]["Medium"]["lifePoints"];
    this->max_life = life_points;
    int cooldown = config["Enemy"]["Medium"]["directionResetCooldown"];
    this->directionResetCooldown = std::chrono::milliseconds(cooldown);
    this->xp_points = config["Enemy"]["Medium"]["xp_points"];

    cooldown = config["Enemy"]["Medium"]["ligthAttackCooldown"];
    this->light_attack_cooldown = std::chrono::milliseconds(cooldown);
    this->light_attack_speed = config["Enemy"]["Medium"]["lightAttackSpeed"];
    this->light_attack_damage = config["Enemy"]["Medium"]["lightAttackDamage"];

    this->right1TexturePath = config["Enemy"]["Medium"]["right1Path"];
    this->right2TexturePath = config["Enemy"]["Medium"]["right2Path"];
    this->left1TexturePath = config["Enemy"]["Medium"]["left1Path"];
    this->left2TexturePath = config["Enemy"]["Medium"]["left2Path"];

    this->lightAttackUpPath = config["Enemy"]["Medium"]["lightAttackUpPath"];
    this->lightAttackDownPath = config["Enemy"]["Medium"]["lightAttackDownPath"];
    this->lightAttackLeftPath = config["Enemy"]["Medium"]["lightAttackLeftPath"];
    this->lightAttackRightPath = config["Enemy"]["Medium"]["lightAttackRightPath"];
}

void EnemyMedium::initShape()
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
    this->realColor = this->sprite.getColor();



    sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();
    this->width_rect = 20;
    this->height_rect = 20;
    this->top_rect = this->height_rect/2;
    this->left_rect = this->width_rect/2;


    this->collisionRect.setSize(sf::Vector2f(spriteBounds.width-this->width_rect, spriteBounds.height-this->height_rect));
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+this->left_rect, spriteBounds.top+spriteBounds.height-this->collisionRect.getGlobalBounds().height));
    this->collisionRect.setFillColor(sf::Color::Red);

}

void EnemyMedium::updateMovement(Robot* robot)
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


    auto now = chrono::steady_clock::now();

    if(now - this->lastTimeChangeDirections > this->directionResetCooldown)
    {
        //Choose if moves horizontally or vertically
        int random = rand() % 2;
        //horizontal movement
        if(random == 0)
        {
            this->setDirectionVelocity(this->facing_direction, this->movementSpeed);
        }
        else{
            
            //move according the robot
            if((enemy_pos.y < robot_pos.y && enemy_pos.y + enemy_bounds.height < robot_pos.y + robot_bounds.height))
            {
                this->setDirectionVelocity(DOWN, this->movementSpeed);
                this->direction = DOWN;
            }
            else if ((enemy_pos.y > robot_pos.y && enemy_pos.y + enemy_bounds.height > robot_pos.y + robot_bounds.height)){
                this->setDirectionVelocity(UP, this->movementSpeed);
                this->direction = UP;
            }
            else{
                this->setVelocity(0.f, 0.f);
            }
        }
        this->lastTimeChangeDirections = now;
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

///////////////////////// Enemy Strong ///////////////////////////
EnemyStrong::EnemyStrong(float start_x, float start_y, std::weak_ptr<SoundManager> soundManager)
{
    enemyType = STRONG;
    this->sprite.setPosition(start_x, start_y);
    this->direction = DOWN;
    this->spriteCounter = 0;
    this->dyingCounter = 0;
    this->damagedCounter = 0;
    this->spriteNumber = 1;
    this->movementSpeed = 0.f;
    this->velocity = sf::Vector2f(0.f, this->movementSpeed);

    this->soundManager = soundManager;

    this->initConfigFile();
    this->initShape();
    this->initAttackTexture();

    this->healthBar = std::make_unique<HealthBar>(30.f, 6.f, this->max_life);
}

void EnemyStrong::initConfigFile()
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

    this->movementSpeed = config["Enemy"]["Strong"]["speed"];
    this->life_points = config["Enemy"]["Strong"]["lifePoints"];
    this->max_life = life_points;
    int cooldown = config["Enemy"]["Strong"]["directionResetCooldown"];
    this->directionResetCooldown = std::chrono::milliseconds(cooldown);
    this->xp_points = config["Enemy"]["Medium"]["xp_points"];

    cooldown = config["Enemy"]["Strong"]["ligthAttackCooldown"];
    this->light_attack_cooldown = std::chrono::milliseconds(cooldown);
    this->light_attack_speed = config["Enemy"]["Strong"]["lightAttackSpeed"];
    this->light_attack_damage = config["Enemy"]["Strong"]["lightAttackDamage"];

    this->right1TexturePath = config["Enemy"]["Strong"]["right1Path"];
    this->right2TexturePath = config["Enemy"]["Strong"]["right2Path"];
    this->left1TexturePath = config["Enemy"]["Strong"]["left1Path"];
    this->left2TexturePath = config["Enemy"]["Strong"]["left2Path"];

    this->lightAttackUpPath = config["Enemy"]["Strong"]["lightAttackUpPath"];
    this->lightAttackDownPath = config["Enemy"]["Strong"]["lightAttackDownPath"];
    this->lightAttackLeftPath = config["Enemy"]["Strong"]["lightAttackLeftPath"];
    this->lightAttackRightPath = config["Enemy"]["Strong"]["lightAttackRightPath"];
}

void EnemyStrong::initShape()
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
    this->realColor = this->sprite.getColor();



    sf::FloatRect spriteBounds = this->sprite.getGlobalBounds();
    this->width_rect = 20;
    this->height_rect = 20;
    this->top_rect = this->height_rect/2;
    this->left_rect = this->width_rect/2;


    this->collisionRect.setSize(sf::Vector2f(spriteBounds.width-this->width_rect, spriteBounds.height-this->height_rect));
    this->collisionRect.setPosition(sf::Vector2f(spriteBounds.left+this->left_rect, spriteBounds.top+spriteBounds.height-this->collisionRect.getGlobalBounds().height));
    this->collisionRect.setFillColor(sf::Color::Red);
}

void EnemyStrong::updateMovement(Robot* robot)
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


    auto now = chrono::steady_clock::now();

    if(now - this->lastTimeChangeDirections > this->directionResetCooldown)
    {
        //Choose if moves horizontally or vertically
        int random = rand() % 2;
        //horizontal movement
        if(random == 0)
        {
            this->setDirectionVelocity(this->facing_direction, this->movementSpeed);
        }
        else{
            
            //move according the robot
            if((enemy_pos.y < robot_pos.y && enemy_pos.y + enemy_bounds.height < robot_pos.y + robot_bounds.height))
            {
                this->setDirectionVelocity(DOWN, this->movementSpeed);
                this->direction = DOWN;
            }
            else if ((enemy_pos.y > robot_pos.y && enemy_pos.y + enemy_bounds.height > robot_pos.y + robot_bounds.height)){
                this->setDirectionVelocity(UP, this->movementSpeed);
                this->direction = UP;
            }
            else{
                this->setVelocity(0.f, 0.f);
            }
        }
        this->lastTimeChangeDirections = now;
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

