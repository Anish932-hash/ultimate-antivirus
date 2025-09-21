#pragma once

#include <string>

namespace Core {

class CoreAPI {

public:

    static void Initialize();

    static void Shutdown();

    static std::string GetStatus();

    static void StartScan(const std::string& path);

    static void EnableRealTimeProtection();

    static void ActivateGodMode();

};

}