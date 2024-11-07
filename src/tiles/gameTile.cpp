#include "tiles/gameTile.hpp"

GameTile::GameTile()
{

}
GameTile::GameTile(std::string textureName, float x, float y, float width, float height){

    this->initSprite(textureName, x, y, width, height);   
}


void GameTile::initSprite(std::string textureName, float x, float y, float width, float height){
    if(!texture.loadFromFile(textureName)){
        std::cout << "Error: Texture Path not found\n";
        return;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);

    sprite.setScale(
        width / sprite.getLocalBounds().width,
        height / sprite.getLocalBounds().height
    );

    pos = sf::Vector2f(x, y);
    sprite.setPosition(pos);
}

const sf::Vector2f & GameTile::getPosition() const
{
    return this->sprite.getPosition();
}

sf::Sprite GameTile::getSprite()
{
    return this->sprite;
}