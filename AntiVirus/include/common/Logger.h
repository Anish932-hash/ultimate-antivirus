#pragma once

#include <string>

namespace Common {

class Logger {

public:

    enum class Level { Debug, Info, Warning, Error };

    static void Log(Level level, const std::string& message);

};

}