#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

#ifndef SOUND_HPP
#define SOUND_HPP

#include <map>
#include <string>

class SoundManager {

private:
    sf::Music music;
    float musicVolume = 100.f;
    float soundVolume = 100.f;
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
    void initConfig();
public:
    SoundManager();
    ~SoundManager();
    void loadSound(const std::string& name, const std::string& filePath);
    void playSound(const std::string& name);
    void loadMusic(const std::string& filePath);
    void playMusic();
    void stopMusic();


};


#endif

