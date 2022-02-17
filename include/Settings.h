#ifndef BATTLESHIP_CPP_SETTINGS_H
#define BATTLESHIP_CPP_SETTINGS_H

#include <map>
#include <string>

enum Setting {
    MARK_MISSES_AROUND, HARD_ENEMY
};

bool fileExists(std::string path);

/**
 * @brief Class that handles setting settings
 */
class Settings {
    std::map<Setting, bool> defaultSettings;
    std::string path;
    std::map<Setting, bool> settings;

public:
    explicit Settings(std::string path = "settings.json");

    void setMarkMissesAround(bool newState);

    void setHardEnemy(bool newState);

    void loadSettings();

    void saveSettings();

    std::map<Setting, bool> getSettings();
};

#endif //BATTLESHIP_CPP_SETTINGS_H
