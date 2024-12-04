#include "tiles/tileManager.hpp"

void printMap(std::vector<std::vector<int>> map)
{
    for(int i=0; i < map.size(); i++)
    {
        for(int j=0; j < map[i].size(); j++)
        {
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

TileManager::TileManager(GamePanelInfo* gpInfo)
{
    this->gpInfo = gpInfo;
    this->initConfigPaths();
    this->initTiles();
    this->loadMap("maps/map1.txt");

    this->gpInfo->setScreenSize(this->map.size(), this->map[0].size());
}

void TileManager::initConfigPaths()
{
    // Open the JSON file
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

    this->ground_path = config["GameTiles"]["groundPath"];
    this->wall_path = config["GameTiles"]["wallPath"];
}

void TileManager::initTiles()
{
    //floor
    this->tiles.push_back(new GameTile());
    this->tiles[0]->initSprite(this->ground_path, 0, 0, this->gpInfo->tileSize, this->gpInfo->tileSize);
    this->tiles[0]->collision = false;

    this->tiles.push_back(new GameTile());
    this->tiles[1]->initSprite(this->wall_path, 0, 0, this->gpInfo->tileSize, this->gpInfo->tileSize);
    this->tiles[1]->collision = true;
}

void TileManager::loadMap(std::string map_path)
{
    std::ifstream file(map_path);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << map_path << std::endl;
        return; // Return empty map on failure
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::vector<int> row;
        int value;

        while (lineStream >> value) { // Read each integer separated by spaces
            if(value > this->tiles.size()-1)
            {
                throw GameException("This tile number does not exist");
            }
            row.push_back(value);
        }

        map.push_back(row); // Add the row to the map
    }

    file.close();
    std::cout << "Loaded Map \n" << std::endl;
    printMap(this->map);
}



void TileManager::render(sf::RenderTarget* target)
{
    float x = 0.f;
    float y = 0.f;

    if(target == nullptr)
        return;
    
    if(this->gpInfo == nullptr || this->map.size() == 0)
        return;

    /*Fill all the tiles of the screen*/
    for(int row=0; row < this->gpInfo->maxScreenRow; row++)
    {
        for(int col=0; col < this->gpInfo->maxScreenCol ; col++)
        {
            int n_tile = this->map[row][col];
            if(n_tile > this->tiles.size()-1)
            {
                //exception
                throw GameException("This tile number does not exist");
            }
                

            this->tiles[n_tile]->sprite.setPosition(sf::Vector2f(x,y));

            target->draw(this->tiles[n_tile]->sprite);

            x += this->gpInfo->tileSize;
        }
        x = 0.f;
        y += this->gpInfo->tileSize;
    }
}


/*
* GETS
 */
std::vector<std::vector<int>> TileManager::getMap()
{
    return this->map;
}

std::vector<GameTile*> TileManager::getTiles()
{
    return this->tiles;
}