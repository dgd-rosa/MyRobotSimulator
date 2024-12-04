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
    this->pointsText.setPosition(350 , 24);
    this->pointsText.setOutlineColor(sf::Color::Black);
    this->pointsText.setString(std::to_string(points) + " X");


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


////////////////////////////////////// Level Header Definition /////////////////////

LevelHeader::LevelHeader()
{
    if(!this->font.loadFromFile("fonts/yoster.ttf"))
    {
        throw GameException("error loading font file");
    }

    this->pointsText.setFont(font);
    this->pointsText.setCharacterSize(26);
    this->pointsText.setFillColor(sf::Color::White);
    this->pointsText.setPosition(170, 24);
    this->pointsText.setOutlineColor(sf::Color::Black);
    this->pointsText.setString("Level: " + std::to_string(level));

}

void LevelHeader::update(unsigned int level)
{
    this->level = level;
    this->pointsText.setString("Level: " + std::to_string(level));
}

void LevelHeader::render(sf::RenderTarget* target)
{
    target->draw(this->pointsText);
}

////////////////////////////////////// Header Definition ///////////////////////

Header::Header(int maxLifePoints, int tileSize)
{
    this->points_header = std::make_unique<PointsHeader>();
    this->level_header = std::make_unique<LevelHeader>();

    this->tileSize = tileSize;
    this->nHearts = maxLifePoints / 2;

    for(int i=0; i < nHearts; i++)
    {
        this->hearts.push_back(std::make_unique<OBJ_Heart>());
    }
}

void Header::update(unsigned int points, unsigned int level, int life_points)
{
    this->points_header->update(points);
    this->level_header->update(level);

    int x = tileSize/2;
    int y = tileSize/2;
    

    //Draw blank hearts
    for(int i=0; i < nHearts; i++)
    {
        hearts[i]->setPosition(sf::Vector2f(x, y));
        hearts[i]->setHeartTexture("blank");
        x += tileSize;
    }

    //Draw Life
    int current_heart = 0;
    int i = 0;
    while(i < life_points)
    {
        this->hearts[current_heart]->setHeartTexture("half");
        i++;
        if(i < life_points){
            this->hearts[current_heart]->setHeartTexture("full");
        }
        i++;
        current_heart++;
    }
}

void Header::render(sf::RenderTarget* target)
{
    this->points_header->render(target);
    this->level_header->render(target);

    for(int i=0; i < nHearts; i++)
    {
        hearts[i]->render(target);
    }
}