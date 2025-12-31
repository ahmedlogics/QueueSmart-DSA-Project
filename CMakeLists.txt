cmake_minimum_required(VERSION 3.10)
project(QueueSmart_Backend)
set(CMAKE_CXX_STANDARD 17)

# Find Threads (Crow needs this)
find_package(Threads REQUIRED)

# Include Directories
include_directories(include)
include_directories(vendor/crow/include)

# Source Files
set(SOURCES
    main.cpp
    src/Services/AuthService.cpp
    src/Services/QueueManager.cpp
    src/Handlers/AuthHandlers.cpp
    src/Handlers/QueueHandlers.cpp
    src/Handlers/UserHandlers.cpp
)

# Create Executable
add_executable(QueueSmart_Backend ${SOURCES})

# Link Libraries
target_link_libraries(QueueSmart_Backend Threads::Threads)