#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

#ifndef BATTERY_HPP
#define BATTERY_HPP

class Battery
{
    public:
        //Attributes
        //Sprites
        sf::Texture green;
        sf::Texture yellow;
        sf::Texture orange;
        sf::Texture red;
        sf::Texture empty;
        sf::Sprite sprite;

        unsigned int battery;

        std::chrono::time_point<std::chrono::steady_clock> lastTimeUpdate;
        std::chrono::milliseconds updateInterval;

        
        Battery();
        void initShape();
        

        void update();
        void boost(unsigned int boostPercentage);
        void render(sf::RenderTarget* target);

};



#endif