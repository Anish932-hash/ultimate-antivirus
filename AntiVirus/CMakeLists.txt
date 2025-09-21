cmake_minimum_required(VERSION 3.20)

project(Antivirus VERSION 1.0.0 LANGUAGES CXX CSharp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable folders for IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find required packages
find_package(SQLite3 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(DotNet REQUIRED)

# Include directories
include_directories(include)
include_directories(src/common)

# Add subdirectories
add_subdirectory(src/common)
add_subdirectory(src/core)
add_subdirectory(src/gui)
add_subdirectory(src/ai)
add_subdirectory(tests)

# Main executable (Console)
add_executable(UltimateAntivirus src/main.cpp)
target_link_libraries(UltimateAntivirus AntivirusCore)

# GUI executable (Standalone WPF)
add_executable(AntivirusGUI WIN32
    src/gui/App.xaml
    src/gui/App.xaml.cs
    src/gui/MainWindow.xaml
    src/gui/MainWindow.xaml.cs
)
set_target_properties(AntivirusGUI PROPERTIES
    DOTNET_TARGET_FRAMEWORK "net6.0-windows"
    WIN32_EXECUTABLE TRUE
)

# Install targets
install(TARGETS UltimateAntivirus AntivirusGUI AntivirusCore
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)