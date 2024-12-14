#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

class HealthBar
{

    private:
        sf::RectangleShape insideRectangle;
        sf::RectangleShape borderRectangle;

        float width, height;
        float inside_width, inside_height;
        float current_width;
        int health;
        int max_health;
        

        void initShape();

    public:
        HealthBar(float width, float height, int max_health);
        ~HealthBar() = default;

        void setPosition(sf::Vector2f pos);
        void update(int health, sf::FloatRect bounds);
        void render(sf::RenderTarget* target);

};

#endif