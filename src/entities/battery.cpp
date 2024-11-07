#include "entities/battery.hpp"

Battery::Battery()
{
    this->battery = 100;
    this->lastTimeUpdate = std::chrono::steady_clock::now();
    this->updateInterval = std::chrono::milliseconds(300);

    this->initShape();
}

void Battery::initShape()
{
    if(!this->green.loadFromFile("images/battery/green.png")){
        std::cout << "ERROR: Battery texture not found!\n\n";
        return;
    }
    this->green.setSmooth(false);


    if(!this->yellow.loadFromFile("images/battery/yellow.png")){
        std::cout << "ERROR: Battery texture not found!\n\n";
        return;
    }
    this->yellow.setSmooth(false);


    //orange
    if(!this->orange.loadFromFile("images/battery/orange.png")){
        std::cout << "ERROR: Battery texture not found!\n\n";
        return;
    }
    this->orange.setSmooth(false);

    //Red
    if(!this->red.loadFromFile("images/battery/red.png")){
        std::cout << "ERROR: Robot texture not found!\n\n";
        return;
    }
    this->red.setSmooth(false);

    //Empty
    if(!this->empty.loadFromFile("images/battery/empty.png")){
        std::cout << "ERROR: Battery texture not found!\n\n";
        return;
    }
    this->empty.setSmooth(false);

    
    
    //Setup Sprite Initially to green
    this->sprite.setTexture(this->green);
    this->sprite.setScale(3,3);
}

void Battery::boost(unsigned int boostPercentage)
{
    std::cout << "Battery BOOST HERE WE GOOOOO!!!" << std::endl;
    this->battery += boostPercentage;
    if(battery > 100)
        this->battery = 100;
}

void Battery::update()
{
    auto now = std::chrono::steady_clock::now();

    if(now - this->lastTimeUpdate > this->updateInterval)
    {
        this->lastTimeUpdate = now;
        
        if(this->battery > 0)
            this->battery -= 1;
    }
}

void Battery::render(sf::RenderTarget* target)
{
    if(this->battery <= 100 && this->battery > 75)
    {
        this->sprite.setTexture(this->green);
    }
    else if(this->battery <= 75 && this->battery > 50)
    {
        this->sprite.setTexture(this->yellow);
    }
    else if(this->battery <= 50 && this->battery > 25)
    {
        this->sprite.setTexture(this->orange);
    }
    else if(this->battery <= 25 && this->battery > 10)
    {
        this->sprite.setTexture(this->red);
    }
    else if(this->battery <= 10 && this->battery <= 0)
    {
        this->sprite.setTexture(this->empty);
    }

    this->sprite.setPosition(sf::Vector2f(750 - this->sprite.getGlobalBounds().width, 10.f));

    target->draw(this->sprite);
}

