#include <chrono>
#include <vector>
#include <SFML/Graphics.hpp>
#include "exceptions/GameException.hpp"
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

struct Score
{
    int score;
    int level;
    int time;

    std::string formattedTime() const;
    std::string toString() const;
};

class Scoreboard
{
    private:
        std::vector<Score> score_list;
        int maxScores = 3;
        int screenWidth, screenHeight;

        sf::Font font;
        sf::Text score1_text;
        sf::Text score2_text;
        sf::Text score3_text;
        std::vector<sf::Text> score_text_list;

        string scoresPath;

        void initConfig();
        void openFile();

        bool compareScores(Score& a, Score& b);

        void initGraphics();
        void setStringToText();

    public:
        Scoreboard(int screenWidth, int screenHeight);
        ~Scoreboard() = default;

        void saveScore(const Score &new_score);
        void render(sf::RenderTarget* target);
};


#endif