#include "entities/battery.hpp"
#include "exceptions/GameException.hpp"
#include <memory> // For smart pointers
#include "objects/OBJ_Heart.hpp"

#ifndef HEADER_HPP
#define HEADER_HPP

class PointsHeader
{   
    private:
        void initConfig();
    public:
        sf::Texture point_symbol_texture;
        sf::Sprite point_symbol_sprite;

        std::string fontPath;
        sf::Font font;
        sf::Text pointsText;
        sf::Text nextLevelText;
        unsigned int points;
        unsigned int nextLevelPoints;

        PointsHeader();

        void update(unsigned int points, unsigned int nextLevelPoints);
        void render(sf::RenderTarget* target);
};

class LevelHeader
{   
    private:
        void initConfig();
    public:
        std::string fontPath;
        sf::Font font;
        sf::Text pointsText;
        unsigned int level;

        LevelHeader();

        void update(unsigned int level);
        void render(sf::RenderTarget* target);
};


class Header
{
    public:

        std::unique_ptr<PointsHeader> points_header;
        std::unique_ptr<LevelHeader> level_header;
        std::vector<std::unique_ptr<OBJ_Heart>> hearts;
        int nHearts = 1;
        int tileSize;

        Header(int maxLifePoints, int tileSize);
        virtual ~Header() = default;

        void update(unsigned int points, unsigned int nextLevelPoints, unsigned int level, int life_points);
        void render(sf::RenderTarget* target);
};




#endif