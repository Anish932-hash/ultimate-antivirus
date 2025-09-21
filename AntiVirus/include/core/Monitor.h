#pragma once

#include <thread>
#include <atomic>

namespace Core {

class Monitor {

public:

    Monitor();

    ~Monitor();

    void StartMonitoring();

    void StopMonitoring();

private:

    void MonitorThread();

    std::thread monitorThread_;

    std::atomic<bool> running_;

};

}