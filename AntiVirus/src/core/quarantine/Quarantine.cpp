#include "Quarantine.h"

#include "Logger.h"

#include <filesystem>

namespace fs = std::filesystem;

void Core::Quarantine::IsolateFile(const std::string& path) {
    try {
        // Move file to quarantine directory
        fs::path quarantinePath = "quarantine/" + fs::path(path).filename().string();
        fs::create_directories("quarantine");
        fs::rename(path, quarantinePath);
        Common::Logger::Log(Common::Logger::Level::Info, "File quarantined: " + path + " -> " + quarantinePath.string());
    } catch (const std::exception& e) {
        Common::Logger::Log(Common::Logger::Level::Error, "Failed to quarantine file: " + std::string(e.what()));
    }
}

void Core::Quarantine::RestoreFile(const std::string& id) {
    try {
        // Restore file from quarantine
        fs::path quarantinePath = "quarantine/" + id;
        fs::path originalPath = "restored/" + id;
        fs::create_directories("restored");
        fs::copy(quarantinePath, originalPath);
        Common::Logger::Log(Common::Logger::Level::Info, "File restored: " + id);
    } catch (const std::exception& e) {
        Common::Logger::Log(Common::Logger::Level::Error, "Failed to restore file: " + std::string(e.what()));
    }
}