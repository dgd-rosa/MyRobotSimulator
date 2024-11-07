#ifndef GAMEPANELINFO_HPP
#define GAMEPANELINFO_HPP

class GamePanelInfo
{
    public:
        int originalTileSize = 16;
        const int scale = 3;

        const int tileSize = originalTileSize * scale;
        int maxScreenCol = 16;
        int maxScreenRow = 12;

        int screenWidth = tileSize * maxScreenCol; //768 pixels
        int screenHeight = tileSize * maxScreenRow; //567 pixels

        GamePanelInfo(){}

        void setScreenSize(int n_rows, int n_cols)
        {
            this->maxScreenRow = n_rows;
            this->maxScreenCol = n_cols;

            screenWidth = tileSize * maxScreenCol;
            screenHeight = tileSize * maxScreenRow;
        }
};

#endif