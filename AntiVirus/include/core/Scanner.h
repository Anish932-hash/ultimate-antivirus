#pragma once

#include <string>
#include <vector>

namespace Core {

class Scanner {

public:

    enum class Result { Clean, Suspicious, Malicious };

    enum class DetectionMethod { Signature, Heuristic, Behavioral, AI };

    struct ScanResult {

        Result result;

        DetectionMethod method;

        std::string details;

        float confidence;

    };

    ScanResult ScanFile(const std::string& filePath);

    std::vector<ScanResult> ScanDirectory(const std::string& dirPath);

private:

    bool CheckSignature(const std::string& hash);

    ScanResult HeuristicAnalysis(const std::string& filePath);

    ScanResult BehavioralAnalysis(const std::string& filePath);

    ScanResult AIAnalysis(const std::string& filePath);

    std::string CalculateSHA256(const std::string& filePath);

};

}