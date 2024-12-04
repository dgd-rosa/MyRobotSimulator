#include "tiles/gameTile.hpp"
#include "tiles/gamePanelInfo.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include "exceptions/GameException.hpp"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

#ifndef TILEMANAGER_HPP
#define TILEMANAGER_HPP

class GamePanelInfo;

/**
 * Class responsible for the tile management
 * 
 *      -stores the types of tiles possible
 *      -renders the map
 */

class TileManager
{
    private:
        std::vector<std::vector<int>> map;
        std::vector<GameTile*> tiles;

        std::string ground_path;
        std::string wall_path;
        //...
        
        void initTiles();
        void initConfigPaths();
    public:
        GamePanelInfo* gpInfo;
        
        TileManager(GamePanelInfo* gp);
        ~TileManager() = default;

        std::vector<std::vector<int>> getMap();
        std::vector<GameTile*> getTiles();

        void loadMap(std::string map_path);
        void update();
        void render(sf::RenderTarget* target);
};

#endif