#include <SFML/Graphics.hpp>
#include "entities/robot.hpp"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "utils/utils.hpp"

using json = nlohmann::json;
using namespace std;


#ifndef UI_HPP
#define UI_HPP

class UI
{
    public:
        float width;
        float height;
        float screenWidth;
        float screenHeight;
        sf::RectangleShape rectangle;
        sf::Texture texture;

        sf::Font font;
        sf::Text title;

        UI(float width, float height, float screenWidth, float screenHeight);

        void initShape(float width, float height);
        void initFont(std::string textureFont);
        void initTexture(std::string texturePath);
        void initRectangle();

        void setTextOriginCenteredRectangle(sf::Text& text);
        void setTextRelativePosition(sf::Text& text, sf::Vector2f pos);
};


class LevelUpUI : public UI
{
    public:
        sf::Text lightAttackDamage;
        sf::Text lightAttackCooldown;
        sf::Text lightAttackSpeed;
        sf::Text movementSpeed;
        sf::Text enterText;

        LevelUpUI(float width, float height, float screenWidth, float screenHeight);
        ~LevelUpUI() = default;

        void initConfig();
        void initTexts();

        
        void update(Robot* robot);
        void render(sf::RenderTarget* target);
};

#endif