#include "CoreAPI.h"
#include <iostream>

int main() {
    std::cout << "Ultimate Antivirus - God Mode Edition" << std::endl;
    std::cout << "Initializing omnipotent protection..." << std::endl;

    Core::CoreAPI::Initialize();
    Core::CoreAPI::EnableRealTimeProtection();
    Core::CoreAPI::ActivateGodMode();

    std::cout << Core::CoreAPI::GetStatus() << std::endl;
    std::cout << "Protection active. Press Enter to exit." << std::endl;

    std::cin.get();

    Core::CoreAPI::Shutdown();

    return 0;
}