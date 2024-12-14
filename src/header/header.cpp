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

    this->initConfig();
    if(!this->font.loadFromFile(this->fontPath))
    {
        throw GameException("error loading font file");
    }

    this->pointsText.setFont(font);
    this->pointsText.setCharacterSize(26);
    this->pointsText.setFillColor(sf::Color::White);
    this->pointsText.setPosition(400 , 24);
    this->pointsText.setOutlineColor(sf::Color::Black);
    this->pointsText.setString(std::to_string(points) + " X");


    auto text_bounds = this->pointsText.getGlobalBounds();
    this->point_symbol_sprite.setPosition(text_bounds.left + text_bounds.width, text_bounds.top - text_bounds.height/2);

    this->nextLevelText.setFont(font);
    this->nextLevelText.setCharacterSize(20);
    this->nextLevelText.setFillColor(sf::Color::White);
    this->nextLevelText.setPosition(400 , 60);
    this->nextLevelText.setOutlineColor(sf::Color::Black);
    this->nextLevelText.setString("To Next Lvl: " + std::to_string(nextLevelPoints));
}

void PointsHeader::initConfig()
{
    std::ifstream file("config.json");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config.json" << std::endl;
        return;
    }

    // Parse the JSON file
    json config;
    try {
        file >> config;
    } catch (const json::parse_error& e) {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
        return;
    }

    this->fontPath = config["UI"]["Font"];
}


void PointsHeader::update(unsigned int points, unsigned int nextLevelPoints)
{
    this->points = points;
    this->pointsText.setString(std::to_string(points) + " X");

    auto text_bounds = this->pointsText.getGlobalBounds();
    this->point_symbol_sprite.setPosition(text_bounds.left + text_bounds.width + 5, text_bounds.top - text_bounds.height/2);


    this->nextLevelPoints = nextLevelPoints;
    this->nextLevelText.setString("To Next Lvl: " + std::to_string(nextLevelPoints));
}

void PointsHeader::render(sf::RenderTarget* target)
{
    target->draw(this->pointsText);
    target->draw(this->point_symbol_sprite);
    target->draw(this->nextLevelText);
}


////////////////////////////////////// Level Header Definition /////////////////////

LevelHeader::LevelHeader()
{
    this->initConfig();
    if(!this->font.loadFromFile(this->fontPath))
    {
        throw GameException("error loading font file");
    }

    this->pointsText.setFont(font);
    this->pointsText.setCharacterSize(26);
    this->pointsText.setFillColor(sf::Color::White);
    this->pointsText.setPosition(200, 24);
    this->pointsText.setOutlineColor(sf::Color::Black);
    this->pointsText.setString("Level: " + std::to_string(level));

}

void LevelHeader::initConfig()
{
    std::ifstream file("config.json");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config.json" << std::endl;
        return;
    }

    // Parse the JSON file
    json config;
    try {
        file >> config;
    } catch (const json::parse_error& e) {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
        return;
    }

    this->fontPath = config["UI"]["Font"];
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
        this->hearts[i]->sprite.setScale(3, 3);
    }
}

void Header::update(unsigned int points, unsigned int nextLevelPoints, unsigned int level, int life_points)
{
    this->points_header->update(points, nextLevelPoints);
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