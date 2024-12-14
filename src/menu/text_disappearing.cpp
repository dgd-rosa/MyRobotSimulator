#include "menu/text_disappearing.hpp"

TextDisappear::TextDisappear(sf::Vector2f pos, unsigned int value)
{
    this->pos = pos;
    this->value = value;
    this->transparency = 255;
    this->initConfig();
    this->initText();
}

void TextDisappear::initConfig()
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

    this->initFont(config["UI"]["Font"]);
}

void TextDisappear::initFont(std::string fontPath)
{
    if (!this->font.loadFromFile(fontPath)) {
        throw GameException("UI: Error loading font!");
    }
}

void TextDisappear::setTransparency(sf::Color &color, float transparency)
{
    if(transparency < 0)
    {
        transparency = 0;
    }
    else if(transparency > 255)
    {
        transparency = 255;
    }

    color.a = transparency;
}

void TextDisappear::initText()
{
    this->text.setFont(this->font);
    this->text.setCharacterSize(16);
    sf::Color color = sf::Color::White;
    this->setTransparency(color, this->transparency);
    this->text.setFillColor(color);
    this->text.setPosition(this->pos);

    std::string str = "+";
    str += Utils::to_string_with_precision(this->value, 0);
    str += " xp";
    this->text.setString(str);
}

void TextDisappear::changeTextTransparency(float value)
{
    auto color = this->text.getFillColor();
    color.a = value;

    this->text.setFillColor(color);
    this->text.getString();
}

float TextDisappear::getTransparency()
{
    return this->transparency;
}

void TextDisappear::update()
{
    this->textCounter++;
    
    if(this->textCounter % textNumber)
    {
        //Move Text
        this->text.move(sf::Vector2f(0.1, -0.1));

        //decrease transparency
        transparency -= textNumber;
        if(transparency < 0)
        {
            transparency = 0;
        }
        this->changeTextTransparency(transparency);

        this->textCounter = 0;
    }
    
}

void TextDisappear::render(sf::RenderTarget* target)
{
    target->draw(this->text);
}