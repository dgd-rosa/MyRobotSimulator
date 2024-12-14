#include "menu/health_bar.hpp"

HealthBar::HealthBar(float width, float height, int max_health)
{
    this->width = width;
    this->height = height;
    this->inside_height = height-2;
    this->inside_width = width-4;

    this->max_health = max_health;
    this->health = max_health;
    this->initShape();   
}

void HealthBar::initShape()
{
    //Border Rectangle;
    borderRectangle.setSize(sf::Vector2f(width, height));
    borderRectangle.setFillColor(sf::Color::Black);
    auto borderBounds = borderRectangle.getLocalBounds();
    borderRectangle.setOrigin(borderBounds.width/2, borderBounds.height/2);


    //Inside Rectangle;
    insideRectangle.setFillColor(sf::Color::Red);
    insideRectangle.setSize(sf::Vector2f(inside_width, inside_height));
    auto insideBounds = insideRectangle.getLocalBounds();
    insideRectangle.setOrigin(insideBounds.width/2, insideBounds.height/2);
}

void HealthBar::setPosition(sf::Vector2f pos)
{
    borderRectangle.setPosition(pos);
    insideRectangle.setPosition(pos);
}


void HealthBar::update(int health, sf::FloatRect bounds)
{
    this->health = health;

    float ratio = static_cast<float>(health) / static_cast<float>(this->max_health);
    
    float current_width = this->inside_width * ratio;

    insideRectangle.setSize(sf::Vector2f(current_width, this->inside_height));

    this->setPosition(sf::Vector2f(bounds.left+bounds.width/2, bounds.top - 3));
}

void HealthBar::render(sf::RenderTarget* target)
{
    target->draw(this->borderRectangle);
    target->draw(this->insideRectangle);
}