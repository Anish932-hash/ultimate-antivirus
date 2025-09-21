#include "common/Logger.h"

#include <iostream>

#include <chrono>

#include <iomanip>

#include <ctime>

void Common::Logger::Log(Level level, const std::string& message) {

    auto now = std::chrono::system_clock::now();

    auto time = std::chrono::system_clock::to_time_t(now);

    std::tm tm;

    localtime_s(&tm, &time);

    std::cout << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " [" << static_cast<int>(level) << "] " << message << std::endl;

}