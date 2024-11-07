#include "entities/battery.hpp"
#include "exceptions/GameException.hpp"
#include <memory> // For smart pointers

#ifndef HEADER_HPP
#define HEADER_HPP

class PointsHeader
{   

    public:
        sf::Texture point_symbol_texture;
        sf::Sprite point_symbol_sprite;

        sf::Font font;
        sf::Text pointsText;
        sf::Text xText;
        unsigned int points;

        PointsHeader();

        void update(unsigned int points);
        void render(sf::RenderTarget* target);
};


class Header
{
    public:

        std::unique_ptr<PointsHeader> points_header;

        Header();
        virtual ~Header() = default;

        void update(unsigned int points);
        void render(sf::RenderTarget* target);
};




#endif