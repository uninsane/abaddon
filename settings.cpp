#include "settings.hpp"
#include <filesystem>
#include <fstream>

SettingsManager::SettingsManager(std::string filename)
    : m_filename(filename) {
    if (!std::filesystem::exists(filename)) {
        std::fstream fs;
        fs.open(filename, std::ios::out);
        fs.close();
    }

    auto rc = m_ini.LoadFile(filename.c_str());
    m_ok = rc == SI_OK;
}

std::string SettingsManager::GetSettingString(const std::string &section, const std::string &key, std::string fallback) const {
    return m_ini.GetValue(section.c_str(), key.c_str(), fallback.c_str());
}

int SettingsManager::GetSettingInt(const std::string &section, const std::string &key, int fallback) const {
    return std::stoul(GetSettingString(section, key, std::to_string(fallback)));
}

bool SettingsManager::GetSettingBool(const std::string &section, const std::string &key, bool fallback) const {
    return GetSettingString(section, key, "false") != "false";
}

bool SettingsManager::IsValid() const {
    return m_ok;
}

void SettingsManager::Close() {
    m_ini.SaveFile(m_filename.c_str());
}

