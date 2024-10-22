#include "robot.hpp"

void Robot::initVariables()
{
    this->movementSpeed = 10.f;
}

void Robot::initShape(std::string texture_path)
{
    if(!this->texture.loadFromFile(texture_path)){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }

    this->texture.setSmooth(false);

    this->sprite.setTexture(this->texture);

    this->sprite.setScale(3, 3);
}


Robot::Robot(float start_x, float start_y, std::string texture_path){
    m_position.x = start_x;
    m_position.y = start_y;

    this->sprite.setPosition(start_x, start_y);

    this->initVariables();
    this->initShape(texture_path);

}

Robot::~Robot(){
}

const sf::Vector2f & Robot::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Robot::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

void Robot::setPosition(const sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void Robot::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x,y);
}


void Robot::updateInput()
{
    //Keyboard input
    //Left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->sprite.move(-this->movementSpeed, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->sprite.move(this->movementSpeed, 0.f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->sprite.move(0.f, -this->movementSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->sprite.move(0.f, this->movementSpeed);
    }
}

void Robot::update(sf::RenderTarget* target)
{
    //Windows bounds collision

    
    this->updateInput();
}

void Robot::render(sf::RenderTarget* target){

    if(target == nullptr)
        return;
    
    target->draw(this->sprite);
}