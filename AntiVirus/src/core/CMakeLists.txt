add_library(AntivirusCore STATIC
    scanner/Scanner.cpp
    monitor/Monitor.cpp
    quarantine/Quarantine.cpp
    network/NetworkProtector.cpp
    quantum/QuantumEngine.cpp
    godmode/GodModeProtector.cpp
    threat/ThreatHunter.cpp
    deception/DeceptionEngine.cpp
    edr/EDRModule.cpp
    api/CoreAPI.cpp
)

target_include_directories(AntivirusCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(AntivirusCore Common OpenSSL::SSL OpenSSL::Crypto)