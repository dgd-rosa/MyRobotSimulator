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
    startText.setPosition(300, 150);  // Positioning the text

    // Scoreboard button
    scoreBoardText.setFont(font);
    scoreBoardText.setString("Scoreboard");
    scoreBoardText.setCharacterSize(50);
    scoreBoardText.setFillColor(defaultColor);
    scoreBoardText.setPosition(300, 250);  // Positioning the text

    // Exit button
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(50);
    exitText.setFillColor(defaultColor);
    exitText.setPosition(300, 350);  // Positioning the text

    
}

void Menu::navigate()
{
    if(this->clock.getElapsedTime() > this->cooldown)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && menuOption > START_GAME)
        {
            currentOption--;
            this->clock.restart();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currentOption < EXIT)
        {
            currentOption++;
            this->clock.restart();
        }
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
    
    if (menuOption == START_GAME) {
        startText.setFillColor(selectedColor);
        scoreBoardText.setFillColor(defaultColor);
        exitText.setFillColor(defaultColor);
    } else if (menuOption == SCOREBOARD) {
        startText.setFillColor(defaultColor);
        scoreBoardText.setFillColor(selectedColor);
        exitText.setFillColor(defaultColor);
    } else if(menuOption == EXIT) {
        startText.setFillColor(defaultColor);
        scoreBoardText.setFillColor(defaultColor);
        exitText.setFillColor(selectedColor);
    }
        
    target->draw(this->startText);
    target->draw(this->scoreBoardText);
    target->draw(this->exitText);
    
}