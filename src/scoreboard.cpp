#include "scoreboard.hpp"
#include <typeinfo>

std::string formatTime(int seconds) {
    int hrs = seconds / 3600;
    int mins = (seconds % 3600) / 60;
    int secs = seconds % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hrs << ":"
        << std::setfill('0') << std::setw(2) << mins << ":"
        << std::setfill('0') << std::setw(2) << secs;

    return oss.str();
}

// Function to convert HH:MM:SS format to seconds
int timeToSeconds(const std::string& time) {
    std::istringstream iss(time);
    int hours, minutes, seconds;
    char colon;
    iss >> hours >> colon >> minutes >> colon >> seconds;
    return hours * 3600 + minutes * 60 + seconds;
}

// Convert time to HH:MM:SS format
std::string Score::formattedTime() const {
    return formatTime(this->time);
}

std::string Score::toString() const
{
    std::string str;

    str += "Score: ";
    str += std::to_string(this->score);
    str += "|Level: ";
    str += std::to_string(this->level);
    str += "|Time: ";
    str += this->formattedTime();

    return str;
}

Scoreboard::Scoreboard(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    this->initConfig();
    this->openFile();
    this->initGraphics();
}

void Scoreboard::initGraphics()
{
    if(this->screenWidth <= 0 || this->screenHeight <= 0)
    {
        throw GameException("Scoreboard: Screen dimensions not valid!");
    }
    
    if (!this->font.loadFromFile("fonts/yoster.ttf")) {
        throw GameException("Scoreboard: Error loading font!");
    }

    // Score 1
    score1_text.setFont(this->font);
    score1_text.setCharacterSize(30);
    score1_text.setFillColor(sf::Color::Yellow);

    auto score1_textBounds = score1_text.getLocalBounds();
    score1_text.setOrigin(sf::Vector2f(score1_textBounds.width/2, score1_textBounds.height/2));
    score1_text.setPosition(screenWidth/2, 150);  // Positioning the text


    //Score 2
    score2_text.setFont(this->font);
    score2_text.setCharacterSize(30);
    score2_text.setFillColor(sf::Color::Yellow);

    auto score2_textBounds = score2_text.getLocalBounds();
    score2_text.setOrigin(sf::Vector2f(score2_textBounds.width/2, score2_textBounds.height/2));
    score2_text.setPosition(screenWidth/2, 250);  // Positioning the text


    // Score 3
    score3_text.setFont(this->font);
    score3_text.setCharacterSize(30);
    score3_text.setFillColor(sf::Color::Yellow);

    auto score3_textBounds = score3_text.getLocalBounds();
    score3_text.setOrigin(sf::Vector2f(score3_textBounds.width/2, score3_textBounds.height/2));
    score3_text.setPosition(screenWidth/2, 350);  // Positioning the text


    score_text_list.push_back(score1_text);
    score_text_list.push_back(score2_text);
    score_text_list.push_back(score3_text);

}

void Scoreboard::initConfig()
{
    // Open the JSON file
    std::ifstream file_json("config.json");
    if (!file_json.is_open()) {
        std::cerr << "Error: Could not open config.json" << std::endl;
        return;
    }

    // Parse the JSON file
    json config;
    try {
        file_json >> config;
    } catch (const json::parse_error& e) {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
        return;
    }

    this->scoresPath = config["Scoreboard"]["scoresFile"];
    this->fontPath = config["UI"]["Font"];
}

bool Scoreboard::compareScores(Score& a, Score& b) {
    return a.score > b.score;
}

void Scoreboard::openFile()
{
    std::ifstream file(this->scoresPath);
    char delimiter = ';';

    //File exists
    if(file.is_open())
    {
        std::string line;

        // Skip header
        std::getline(file, line);

        // Read each line
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string scoreStr, levelStr, timeStr;

            if (std::getline(iss, scoreStr, delimiter) &&
                std::getline(iss, levelStr, delimiter) &&
                std::getline(iss, timeStr)) 
            {
             
                Score newScore = {0};
                newScore.score = std::stoi(scoreStr);
                newScore.level = std::stoi(levelStr);
                newScore.time = timeToSeconds(timeStr);

                this->score_list.push_back(newScore);
            }
        }
    }
}
void Scoreboard::saveScore(const Score &new_score)
{
    std::ofstream file(this->scoresPath);
    std::string delimiter = ";";

    if (file.is_open()) {

        // Write header
        file << "Score,Level,Time\n";

        // Add the new score
        score_list.push_back(new_score);

        // Sort scores by descending score
        std::sort(score_list.begin(), score_list.end(), [](const Score& a, const Score& b) {
            return a.score > b.score;
        });

        // Keep only the top 3
        if (score_list.size() > 3) {
            score_list.resize(3);
        }

        // Write each score entry
        for(const auto& entry : this->score_list) {
            file << entry.score << delimiter << entry.level << delimiter << entry.formattedTime() << "\n";
        }

        file.close();
    }
    else
    {
        std::cout << "File does not exist. Creating file: " << scoresPath << std::endl;
    }
    
}

void Scoreboard::setStringToText()
{
    std::string str;
    int i = 0;
    int begin = 150;
    int jump = 100;

    while(i < this->score_list.size())
    {
        str = std::to_string(i+1) + "# ";
        str += score_list[i].toString();
        score_text_list[i].setString(str);

        auto score1_textBounds = score_text_list[i].getLocalBounds();
        score_text_list[i].setOrigin(sf::Vector2f(score1_textBounds.width/2, score1_textBounds.height/2));
        score_text_list[i].setPosition(screenWidth/2, begin + i*jump);  // Positioning the text

        i++;
    }

    // If there are not enough scores
    while(i < this->maxScores)
    {
        score_text_list[i].setString(std::to_string(i+1) + "# Score not Saved");

        auto score1_textBounds = score_text_list[i].getLocalBounds();
        score_text_list[i].setOrigin(sf::Vector2f(score1_textBounds.width/2, score1_textBounds.height/2));
        score_text_list[i].setPosition(screenWidth/2, begin + i*jump);  // Positioning the text

        i++;
    }
}

void Scoreboard::render(sf::RenderTarget* target)
{
    this->setStringToText();

    for(const auto& text : this->score_text_list)
    {
        target->draw(text);
    }
    
}