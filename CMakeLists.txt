cmake_minimum_required(VERSION 3.10)
project(SDL_Test)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the SDL2 package. This command searches for the library files.
# The "REQUIRED" keyword will cause CMake to stop with an error if it can't find SDL2.
find_package(SDL2 REQUIRED)

# Add your executable. This creates a program named "SDL_Project" from main.cpp.
add_executable(SDL_Test src/main.cpp
        src/Game.cpp
        src/Game.h
        src/Player.cpp
        src/Player.h
        src/Level.cpp
        src/Level.h
        src/TileMap.cpp
        src/TileMap.h
        src/Entity.cpp
        src/Entity.h)

#include the src directory
target_include_directories(SDL_Test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Link the SDL2 libraries to your executable.
# ${SDL2_LIBRARIES} is a variable that find_package() created for us.
target_link_libraries(SDL_Test PUBLIC ${SDL2_LIBRARIES})