#include <SFML/Graphics.hpp>
#include "gameTile.hpp"
#include <vector>

#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP


class GameWorld{
    sf::Vector2i robotPos;
    std::vector<sf::Vector2i> obstaclesPos;

    void setUpInitialState();
    void setUpObstaclesPos();
    void setUpTiles();

    public:
        std::vector<std::vector<GameTile * > > m_tiles;
        int gridLength;

        GameWorld();     
};


#endif