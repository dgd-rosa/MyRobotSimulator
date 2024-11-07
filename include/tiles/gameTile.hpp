#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef GAMETILE_HPP
#define GAMETILE_HPP

class GameTile {
    public:
        sf::Vector2f pos;
        sf::Texture texture;
        sf::Sprite sprite;

        bool collision = false;


        GameTile();
        GameTile(std::string textureName, float x, float y, float width, float height);

        //Acessors
        const sf::Vector2f & getPosition() const;

        //Get
        sf::Sprite getSprite();

        void initSprite(std::string textureName, float x, float y ,float width, float height);
};

#endif