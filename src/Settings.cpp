#include "../include/Settings.h"
#include <fstream>
#include <json.hpp>

/**
 * Checks if the specified file exists
 * @param path path to the file to check
 * @return true if it exists, false if it doesn't
 *
 * Replacement for std::filesystem::exists because programs compiled with it don't run
 */
bool fileExists(std::string path) {
    std::ifstream f(path.c_str());
    return f.good();
}

/**
 * @brief Initializes settings by loading the default ones
 * @param path path to the settings file
 */
Settings::Settings(std::string path) {
    this->defaultSettings = std::map<Setting, bool>{
            {Setting::MARK_MISSES_AROUND, true},
            {Setting::HARD_ENEMY,         false}
    };
    this->path = path;
    this->settings = this->defaultSettings;
}

/**
 * @brief Sets the "Mark misses around sunken ships" setting
 * @param newState new state for this setting
 */
void Settings::setMarkMissesAround(bool newState) {
    this->settings[Setting::MARK_MISSES_AROUND] = newState;
}

/**
 * @brief Sets the "Harder enemy" setting
 * @param newState new state for this setting
 */
void Settings::setHardEnemy(bool newState) {
    this->settings[Setting::HARD_ENEMY] = newState;
}

/**
 * @brief Loads settings from the specified settings file
 */
void Settings::loadSettings() {
    if (!fileExists(this->path)) {
        return;
    } else {
        std::fstream settingsFile(this->path);
        std::stringstream ss;
        ss << settingsFile.rdbuf();
        settingsFile.close();
        std::string content = ss.str();
        nlohmann::json settingsJson = nlohmann::json::parse(content);
        this->settings[Setting::MARK_MISSES_AROUND] = settingsJson.value("mark_misses_around", true);
        this->settings[Setting::HARD_ENEMY] = settingsJson.value("hard_enemy", false);
    }
}

/**
 * @brief Saves settings to the specified settings file
 */
void Settings::saveSettings() {
    nlohmann::json settingsJson = {
            {"mark_misses_around", this->settings[Setting::MARK_MISSES_AROUND]},
            {"hard_enemy",         this->settings[Setting::HARD_ENEMY]}
    };
    std::fstream settingsFile;
    settingsFile.open(this->path, std::ios::out);
    settingsFile << std::setw(4) << settingsJson;
    settingsFile.close();
}

std::map<Setting, bool> Settings::getSettings() {
    return this->settings;
}
