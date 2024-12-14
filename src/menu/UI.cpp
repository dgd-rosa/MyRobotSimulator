#include "menu/UI.hpp"

UI::UI(float width, float height, float screenWidth, float screenHeight)
{
    this->width = width;
    this->height = height;
    this->screenHeight = screenHeight;
    this->screenWidth = screenWidth;

    this->initRectangle();
}

void UI::initRectangle()
{
    this->rectangle.setSize(sf::Vector2f(width, height));
    this->rectangle.setOrigin(width/2, height/2);
    this->rectangle.setPosition(sf::Vector2f(screenWidth/2, screenHeight/2));
    this->rectangle.setFillColor(sf::Color(139, 69, 19));
}

void UI::initFont(std::string fontPath)
{
    if (!this->font.loadFromFile(fontPath)) {
        throw GameException("UI: Error loading font!");
    }

    this->title.setFont(this->font);
}

void UI::initTexture(std::string texturePath)
{
    if(!this->texture.loadFromFile(texturePath))
    {
        throw GameException("UI: Error loading Texture!");
    }

    this->rectangle.setTexture(&this->texture);    
}

void UI::setTextOriginCenteredRectangle(sf::Text& text)
{
    auto textBounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f));
}

void UI::setTextRelativePosition(sf::Text& text, sf::Vector2f pos)
{
    auto rectangleBounds = this->rectangle.getGlobalBounds();
    text.setPosition(rectangleBounds.left + pos.x, rectangleBounds.top + pos.y);
}

///////////////////////////////////////////// LevelUpUI /////////////////////////

LevelUpUI::LevelUpUI(float width, float height, float screenWidth, float screenHeight)
    : UI(width, height, screenWidth, screenHeight)
{
    this->initConfig();
    this->initTexts();

    this->title.setString("Level Up");
    this->title.setCharacterSize(28);
    this->title.setFillColor(sf::Color::Yellow);
    this->setTextOriginCenteredRectangle(this->title);
    this->setTextRelativePosition(title, sf::Vector2f(width/2, 20));
}

void LevelUpUI::initConfig()
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

void LevelUpUI::initTexts()
{
    this->lightAttackDamage.setFont(font);
    this->lightAttackDamage.setFillColor(sf::Color::Yellow);
    this->lightAttackDamage.setCharacterSize(18);
    this->lightAttackDamage.setString("Level Up");

    this->lightAttackDamage.setFont(font);
    this->lightAttackDamage.setFillColor(sf::Color::White);
    this->lightAttackDamage.setCharacterSize(18);
    this->lightAttackDamage.setString("");

    this->lightAttackCooldown.setFont(font);
    this->lightAttackCooldown.setFillColor(sf::Color::White);
    this->lightAttackCooldown.setCharacterSize(18);
    this->lightAttackCooldown.setString("");

    this->lightAttackSpeed.setFont(font);
    this->lightAttackSpeed.setFillColor(sf::Color::White);
    this->lightAttackSpeed.setCharacterSize(18);
    this->lightAttackSpeed.setString("");

    this->movementSpeed.setFont(font);
    this->movementSpeed.setFillColor(sf::Color::White);
    this->movementSpeed.setCharacterSize(18);
    this->movementSpeed.setString("");

    this->enterText.setFont(font);
    this->enterText.setFillColor(sf::Color::White);
    this->enterText.setCharacterSize(14);
    this->enterText.setString("Press [SPACE] to continue...");

    sf::FloatRect boundsEnterText = enterText.getLocalBounds();
    this->enterText.setOrigin(sf::Vector2f(boundsEnterText.width/2, boundsEnterText.height/2));
    this->setTextRelativePosition(this->enterText, sf::Vector2f(width/2, height - boundsEnterText.height - 5));

}

void LevelUpUI::update(Robot* robot)
{
    std::string str0 = "Level Up ";
    str0 += std::to_string(robot->getLevel());
    this->title.setString(str0);
    this->setTextOriginCenteredRectangle(this->title);
    this->setTextRelativePosition(title, sf::Vector2f(width/2, 20));

    std::string str = "Light Attack Damage: ";
    str += std::to_string(robot->getLightAttackDamage());
    this->lightAttackDamage.setString(str);
    this->setTextRelativePosition(lightAttackDamage, sf::Vector2f(20, 50));

    std::string str2 = "Light Attack Cooldown: ";
    str2 += Utils::to_string_with_precision(robot->getLightAttackCooldown(), 2);
    str2 += " s";
    this->lightAttackCooldown.setString(str2);
    this->setTextRelativePosition(lightAttackCooldown, sf::Vector2f(20, 80));

    std::string str3 = "Light Attack Speed: ";
    str3 += Utils::to_string_with_precision(robot->getLightAttackSpeed(), 2);
    this->lightAttackSpeed.setString(str3);
    this->setTextRelativePosition(lightAttackSpeed, sf::Vector2f(20, 110));

    std::string str4 = "Movement Speed: ";
    str4 += Utils::to_string_with_precision(robot->getMovementSpeed(), 2);
    this->movementSpeed.setString(str4);
    this->setTextRelativePosition(movementSpeed, sf::Vector2f(20, 140));
}

void LevelUpUI::render(sf::RenderTarget* target)
{
    target->draw(rectangle);

    target->draw(title);
    target->draw(lightAttackDamage);
    target->draw(lightAttackCooldown);
    target->draw(lightAttackSpeed);
    target->draw(movementSpeed);
    target->draw(enterText);
}