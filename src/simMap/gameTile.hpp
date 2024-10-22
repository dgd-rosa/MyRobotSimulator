#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef GAMETILE_HPP
#define GAMETILE_HPP

class GameTile {
    public:
        bool isPassable;
        sf::Vector2f m_pos;
        sf::Texture m_texture;
        sf::Sprite m_sprite;

        GameTile(std::string, float, float, bool);
        bool setUpSprite(std::string);
};

#endif