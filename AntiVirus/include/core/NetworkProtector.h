#pragma once

#include <string>
#include <vector>

namespace Core {

class NetworkProtector {

public:

    void EnableFirewall();

    void BlockPhishing(const std::string& url);

    void ScanWiFi();

    void FilterDNS(const std::string& domain);

    void DetectIntrusion();

    void SetupVPN();

    void MonitorTraffic();

    std::vector<std::string> GetBlockedDomains();

private:

    std::vector<std::string> blockedDomains;

};

}