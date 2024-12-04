#include "objects/OBJ_Heart.hpp"

OBJ_Heart::OBJ_Heart()
{
    try{
        // Open the JSON file
        std::ifstream file("config.json");
        if (!file.is_open()) {
            std::cerr << "Error: Could not open config.json" << std::endl;
            return;
        }

        // Parse the JSON file
        json config;
        file >> config;
        
        this->texture_path = config["Objects"]["Heart"]["blank_path"];
        this->texture2_path = config["Objects"]["Heart"]["half_path"];
        this->texture3_path = config["Objects"]["Heart"]["full_path"];

        this->initShape();

    }catch(std::exception& e)
    {
        throw GameException("Error in Heart Object Constructor");
    }
}

void OBJ_Heart::initShape()
{
    if(!this->texture.loadFromFile(this->texture_path))
    {
        throw GameException("Could not load Blank Heart Texture");
    }

    if(!this->texture2.loadFromFile(this->texture2_path))
    {
        throw GameException("Could not load Half Heart Texture");
    }

    if(!this->texture3.loadFromFile(this->texture3_path))
    {
        throw GameException("Could not load Full Heart Texture");
    }
    
    this->texture.setSmooth(false);
    this->texture2.setSmooth(false);
    this->texture3.setSmooth(false);


    this->sprite.setTexture(this->texture);
    this->sprite.scale(2,2);
    this->bounds = this->sprite.getGlobalBounds();
}

void OBJ_Heart::setHeartTexture(std::string string)
{
    if(string == "blank")
    {
        this->sprite.setTexture(this->texture);
    }
    else if(string == "half")
    {
        this->sprite.setTexture(this->texture2);
    }
    else if(string == "full")
    {
        this->sprite.setTexture(this->texture3);
    }
    else
    {
        // Do Nothing
    }
}