#include <SFML/Graphics.hpp>
#include <iostream>
#include "exceptions/GameException.hpp"

#ifndef MENU_HPP
#define MENU_HPP

enum MenuOptions
{
    START_GAME=0,
    EXIT=1
};

class Menu
{
    public:
        int currentOption = 0;  // Tracks the selected menu option
        MenuOptions menuOption = START_GAME;
        sf::Font font;
        sf::Text startText;
        sf::Text exitText;
        sf::Text test;

        sf::Color defaultColor = sf::Color::White;
        sf::Color selectedColor = sf::Color::Yellow;

    
        Menu();

        void navigate();
        bool isEnterPressed();
        void update();
        void render(sf::RenderTarget* target);
};

#endif