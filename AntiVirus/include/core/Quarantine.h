#pragma once

#include <string>

namespace Core {

class Quarantine {

public:

    void IsolateFile(const std::string& path);

    void RestoreFile(const std::string& id);

};

}