#include "menu/menu.hpp"

Menu::Menu(int screenWidth, int screenHeight, std::shared_ptr<SoundManager> soundManager)
{
    this->soundManager = soundManager;

    if(screenWidth <= 0 || screenHeight <= 0)
    {
        throw GameException("Menu: Screen dimensions not valid!");
    }
    
    this->initConfig();
    if (!this->font.loadFromFile(this->fontPath)) {
        throw GameException("Scoreboard: Error loading font!");
    }

    // Start button
    startText.setFont(this->font);
    startText.setString("Start Game");
    startText.setCharacterSize(50);
    startText.setFillColor(defaultColor);

    auto startTextBounds = startText.getLocalBounds();
    startText.setOrigin(sf::Vector2f(startTextBounds.width/2, startTextBounds.height/2));
    startText.setPosition(screenWidth/2, 150);  // Positioning the text

    // Scoreboard button
    scoreBoardText.setFont(font);
    scoreBoardText.setString("Scoreboard");
    scoreBoardText.setCharacterSize(50);
    scoreBoardText.setFillColor(defaultColor);

    auto scoreBoardTextBounds = scoreBoardText.getLocalBounds();
    scoreBoardText.setOrigin(sf::Vector2f(scoreBoardTextBounds.width/2, scoreBoardTextBounds.height/2));
    scoreBoardText.setPosition(screenWidth/2, 250);  // Positioning the text

    // Exit button
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(50);
    exitText.setFillColor(defaultColor);

    auto exitTextBounds = exitText.getLocalBounds();
    exitText.setOrigin(sf::Vector2f(exitTextBounds.width/2, exitTextBounds.height/2));
    exitText.setPosition(screenWidth/2, 350);  // Positioning the text



    this->scoreboard = std::make_unique<Scoreboard>(screenWidth, screenHeight);
}

void Menu::initConfig()
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

void Menu::handleKeyPressedEvents(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(this->currentMenuState == MAIN_MENU)
        {
            this->navigate(event);
        }
        else if(this->currentMenuState == SCOREBOARD_MENU)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                this->currentMenuState = MAIN_MENU;
            }
        }
    }
}
void Menu::navigate(sf::Event &event)
{
    if(this->clock.getElapsedTime() > this->cooldown)
    {
        if(event.key.code == sf::Keyboard::Up && menuOption > START_GAME)
        {
            currentOption--;
            this->clock.restart();
        }
        else if(event.key.code == sf::Keyboard::Down && currentOption < EXIT)
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

void Menu::render(sf::RenderTarget* target)
{
    if(target == nullptr)
        throw GameException("Render target is null");
    
    if(currentMenuState == MAIN_MENU)
    {
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
    else if(currentMenuState == SCOREBOARD_MENU)
    {
        scoreboard->render(target);
    }   
    
    
}