#include "Settings.h"
#include <filesystem>
#include <fstream>
#include <json.hpp>

Settings::Settings(std::string path) {

}

void Settings::setMarkMissesAround(bool newState) {

}

void Settings::setHardEnemy(bool newState) {

}

/**
 * @brief Loads settings from the specified settings file
 */
void Settings::loadSettings() {
    if(!std::filesystem::exists(this->path)) {
        return;
    } else {
        std::fstream settingsFile(this->path);
        std::stringstream ss;
        ss << settingsFile.rdbuf();
        std::string content = ss.str();
        nlohmann::json settingsJson = nlohmann::json::parse(content);
        this->settings[Setting::MARK_MISSES_AROUND] = settingsJson.value("mark_misses_around", true);
        this->settings[Setting::HARD_ENEMY] = settingsJson.value("hard_enemy", false);
    }
}

void Settings::saveSettings() {

}

std::map<Setting, bool> Settings::getSettings() {
    return std::map<Setting, bool>();
}
