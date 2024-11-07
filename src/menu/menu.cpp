#include "menu/menu.hpp"

Menu::Menu()
{
    
    if (!this->font.loadFromFile("fonts/yoster.ttf")) {
        throw GameException("Error loading font!");
    }

    // Start button
    startText.setFont(this->font);
    startText.setString("Start Game");
    startText.setCharacterSize(50);
    startText.setFillColor(defaultColor);
    startText.setPosition(300, 200);  // Positioning the text

    // Exit button
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(50);
    exitText.setFillColor(defaultColor);
    exitText.setPosition(300, 300);  // Positioning the text

    
}

void Menu::navigate()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && currentOption > 0)
    {
        currentOption--;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentOption < 1)
    {
        currentOption++;
    }
    menuOption = static_cast<MenuOptions>(currentOption);
}

bool Menu::isEnterPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}

void Menu::update()
{
    this->navigate();
}

void Menu::render(sf::RenderTarget* target)
{
    if(target == nullptr)
        throw GameException("Render target is null");
    
    if (currentOption == 0) {
        startText.setFillColor(selectedColor);
        exitText.setFillColor(defaultColor);
    } else if (currentOption == 1) {
        startText.setFillColor(defaultColor);
        exitText.setFillColor(selectedColor);
    }
        
    target->draw(startText);
    target->draw(this->exitText);
    
}