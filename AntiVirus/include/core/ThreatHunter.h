#pragma once

#include <string>
#include <vector>

namespace Core {

class ThreatHunter {

public:

    void HuntThreats();

    void AnalyzeTTPs();

    std::vector<std::string> FindHiddenThreats();

    void ProactiveSearch();

};

}