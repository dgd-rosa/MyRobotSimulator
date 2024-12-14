#include <SFML/Graphics.hpp>
#include "exceptions/GameException.hpp"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include "utils/utils.hpp"

using json = nlohmann::json;
using namespace std;

#ifndef TEXT_DISAPPEARING_HPP
#define TEXT_DISAPPEARING_HPP


class TextDisappear
{
    private:
        void initConfig();
        void initFont(std::string fontPath);
        void initText();
        void setTransparency(sf::Color &color, float transparency);
        void changeTextTransparency(float value);
    public:
        sf::Font font;
        sf::Text text;
        sf::Vector2f pos;
        float value;
        float transparency;
        float vel_x, vely;

        int textCounter = 0;
        int textNumber = 5;

        TextDisappear(sf::Vector2f pos, unsigned int value);
        ~TextDisappear() = default;

        float getTransparency();

        void update();
        void render(sf::RenderTarget* target);

};

#endif