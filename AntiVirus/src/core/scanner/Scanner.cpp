#include "Scanner.h"

#include "Database.h"

#include "Logger.h"

#include <filesystem>

#include <fstream>

#include <openssl/sha.h>

#include <algorithm>

namespace fs = std::filesystem;

std::string Core::Scanner::CalculateSHA256(const std::string& filePath) {

    std::ifstream file(filePath, std::ios::binary);

    if (!file) return "";

    SHA256_CTX sha256;

    SHA256_Init(&sha256);

    char buffer[8192];

    while (file.read(buffer, sizeof(buffer))) {

        SHA256_Update(&sha256, buffer, file.gcount());

    }

    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_Final(hash, &sha256);

    std::string result;

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {

        char buf[3];

        sprintf(buf, "%02x", hash[i]);

        result += buf;

    }

    return result;

}

Core::Scanner::ScanResult Core::Scanner::ScanFile(const std::string& filePath) {

    Common::Logger::Log(Common::Logger::Level::Info, "Scanning file: " + filePath);

    std::string hash = CalculateSHA256(filePath);

    if (!hash.empty() && CheckSignature(hash)) {

        return {Result::Malicious, DetectionMethod::Signature, "Known malware signature", 1.0f};

    }

    auto heuristic = HeuristicAnalysis(filePath);

    if (heuristic.result != Result::Clean) {

        return heuristic;

    }

    auto behavioral = BehavioralAnalysis(filePath);

    if (behavioral.result != Result::Clean) {

        return behavioral;

    }

    auto ai = AIAnalysis(filePath);

    if (ai.result != Result::Clean) {

        return ai;

    }

    return {Result::Clean, DetectionMethod::Signature, "No threats detected", 1.0f};

}

std::vector<Core::Scanner::ScanResult> Core::Scanner::ScanDirectory(const std::string& dirPath) {

    std::vector<ScanResult> results;

    for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {

        if (fs::is_regular_file(entry)) {

            results.push_back(ScanFile(entry.path().string()));

        }

    }

    return results;

}

bool Core::Scanner::CheckSignature(const std::string& hash) {

    Common::Database db("antivirus.db");

    std::string sql = "SELECT id FROM signatures WHERE hash = '" + hash + "' LIMIT 1";

    auto results = db.Query(sql);

    return !results.empty();

}

Core::Scanner::ScanResult Core::Scanner::HeuristicAnalysis(const std::string& filePath) {

    try {

        auto size = fs::file_size(filePath);

        if (size > 100 * 1024 * 1024) { // 100MB

            return {Result::Suspicious, DetectionMethod::Heuristic, "Unusually large file", 0.7f};

        }

        std::string ext = fs::path(filePath).extension().string();

        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

        if (ext == ".exe" || ext == ".dll") {

            // Check for suspicious strings

            std::ifstream file(filePath, std::ios::binary);

            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            if (content.find("CreateRemoteThread") != std::string::npos) {

                return {Result::Suspicious, DetectionMethod::Heuristic, "Contains suspicious API calls", 0.8f};

            }

        }

    } catch (const std::exception& e) {

        Common::Logger::Log(Common::Logger::Level::Warning, "Heuristic analysis error: " + std::string(e.what()));

    }

    return {Result::Clean, DetectionMethod::Heuristic, "No heuristic flags", 1.0f};

}

Core::Scanner::ScanResult Core::Scanner::BehavioralAnalysis(const std::string& filePath) {

    // TODO: Implement behavioral analysis

    return {Result::Clean, DetectionMethod::Behavioral, "No behavioral anomalies", 1.0f};

}

Core::Scanner::ScanResult Core::Scanner::AIAnalysis(const std::string& filePath) {

    // TODO: Call AI module

    return {Result::Clean, DetectionMethod::AI, "AI analysis clean", 1.0f};

}