#include "sound/sound.hpp"

SoundManager::SoundManager()
{
    initConfig();
}

SoundManager::~SoundManager()
{
    // Explicitly stop and clear all sounds
    for (auto& pair : sounds) {
        pair.second.stop();
    }
    sounds.clear();

    soundBuffers.clear();

    music.stop();
}

void SoundManager::initConfig()
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

    std::string musicPath = config["SoundManager"]["GameMusicPath"];
    this->musicVolume = config["SoundManager"]["MusicVolume"];
    loadMusic(musicPath);

    this->soundVolume = config["SoundManager"]["SoundVolume"];
    std::string hitSoundPath = config["SoundManager"]["HitSoundPath"];
    loadSound("hit", hitSoundPath);

    std::string lightAttackSoundPath = config["SoundManager"]["LightAttackSoundPath"];
    loadSound("light_attack", lightAttackSoundPath);

    std::string pickBoostSoundPath = config["SoundManager"]["PickBoostSoundPath"];
    loadSound("pick_boost", pickBoostSoundPath);

    std::string pickScrewSoundPath = config["SoundManager"]["PickScrewSoundPath"];
    loadSound("pick_screw", pickScrewSoundPath);

    std::string menuClickSoundPath = config["SoundManager"]["MenuClickSoundPath"];
    loadSound("menu_click", menuClickSoundPath);
}

void SoundManager::loadSound(const std::string& name, const std::string& filePath) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(filePath)) {
        soundBuffers[name] = buffer;
        sounds[name].setBuffer(soundBuffers[name]);
    }
}

void SoundManager::playSound(const std::string& name) {
    if (sounds.count(name) > 0) {
        sounds[name].play();
        sounds[name].setVolume(this->soundVolume);
    }
}

void SoundManager::loadMusic(const std::string& filePath) {
    if (music.openFromFile(filePath)) {
        music.setLoop(true);
        music.setVolume(this->musicVolume);
    }
}

void SoundManager::playMusic() {
    music.play();
}

void SoundManager::stopMusic() {
    music.stop();
}
