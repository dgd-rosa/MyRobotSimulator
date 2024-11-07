#include "header/header.hpp"

////////////////////////////////////// Points Header Definition ///////////////////////

PointsHeader::PointsHeader()
{
    if(!this->point_symbol_texture.loadFromFile("images/objects/screw.png"))
    {
        throw GameException("error loading point symbol file");
    }
    this->point_symbol_texture.setSmooth(false);
    this->point_symbol_sprite.setTexture(this->point_symbol_texture);
    this->point_symbol_sprite.setScale(1.75, 1.75);

    if(!this->font.loadFromFile("fonts/yoster.ttf"))
    {
        throw GameException("error loading font file");
    }

    this->pointsText.setFont(font);
    this->pointsText.setCharacterSize(26);
    this->pointsText.setFillColor(sf::Color::White);
    this->pointsText.setPosition(10 , 5);
    this->pointsText.setOutlineColor(sf::Color::Black);
    this->pointsText.setString(std::to_string(points) + " X");

    this->xText.setFont(font);
    this->xText.setCharacterSize(26);
    this->xText.setFillColor(sf::Color::White);
    this->xText.setPosition(26 * 3, 5);
    this->xText.setOutlineColor(sf::Color::Black);
    this->xText.setString(std::string("X"));



    auto text_bounds = this->pointsText.getGlobalBounds();
    this->point_symbol_sprite.setPosition(text_bounds.left + text_bounds.width, text_bounds.top - text_bounds.height/2);

}



void PointsHeader::update(unsigned int points)
{
    this->points = points;
    this->pointsText.setString(std::to_string(points) + " X");

    auto text_bounds = this->pointsText.getGlobalBounds();
    this->point_symbol_sprite.setPosition(text_bounds.left + text_bounds.width + 5, text_bounds.top - text_bounds.height/2);
}

void PointsHeader::render(sf::RenderTarget* target)
{
    target->draw(this->pointsText);
    target->draw(this->point_symbol_sprite);
}




////////////////////////////////////// Header Definition ///////////////////////

Header::Header()
{
    std::cout << "Constructor " << std::endl;
    this->points_header = std::make_unique<PointsHeader>();
}

void Header::update(unsigned int points)
{
    this->points_header->update(points);
}

void Header::render(sf::RenderTarget* target)
{
    this->points_header->render(target);
}