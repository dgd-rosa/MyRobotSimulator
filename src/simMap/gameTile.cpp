#include "gameTile.hpp"

GameTile::GameTile(std::string textureName, float x, float y, bool passable){

    if(!setUpSprite(textureName)){
        std::cout << "Error: Texture Path not found\n";
        return;
    }

    m_pos = sf::Vector2f(x, y);
    m_sprite.setPosition(m_pos);

    isPassable = passable;
}

bool GameTile::setUpSprite(std::string textureName){
    if(!m_texture.loadFromFile(textureName)){
        return false;
    }
    m_texture.setSmooth(true);
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));

    return true;
}