#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef ROBOT_HPP
#define ROBOT_HPP

using namespace std;


struct Position{
    int x;
    int y;
};

class Robot{
    private:
        Position m_position;

        //Texture
        sf::Texture texture;
        sf::Sprite sprite;

        float movementSpeed;


        void initShape(std::string texture_path);
        void initVariables();

    public:
        Robot(float start_x=0.f, float start_y=0.f, std::string texture_path="images/Astro_D.png");
        virtual ~Robot();

        //Accessor
        const sf::Vector2f& getPos() const;
        const sf::FloatRect getBounds() const;

        //Modifiers
        void setPosition(const sf::Vector2f pos);
        void setPosition(const float x, const float y);

        //Gets
        Position getPosition();

        // Functions
        void updateInput();
        void update(sf::RenderTarget* target);
        void render(sf::RenderTarget* target);
};

#endif