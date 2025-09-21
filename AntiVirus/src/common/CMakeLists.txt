add_library(Common STATIC
    logging/Logger.cpp
    crypto/Crypto.cpp
    ipc/IPC.cpp
    utils/Utils.cpp
    Database.cpp
)

target_include_directories(Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(Common SQLite::SQLite3)