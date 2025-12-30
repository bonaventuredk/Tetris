cmake_minimum_required(VERSION 3.28)
project(Tetrix)

set(CMAKE_CXX_STANDARD 17)

# Exemples for Windows of paths to libraries if they're not found automatically :

list(APPEND CMAKE_PREFIX_PATH "C:/Program\ Files\ (x86)/Library/C++/Catch2")
list(APPEND CMAKE_PREFIX_PATH "C:/Program\ Files/Library/C++/SFML-3.0.2")


set(SFML_STATIC_LIBRARIES ON) 

find_package(Catch2 3 REQUIRED)
find_package(SFML 3 COMPONENTS Graphics Audio REQUIRED)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System) 

include_directories(core/include ui/include)
add_library(tetris_core core/src/core_class.cpp)
add_library(tetris_ui ui/src/ui.cpp)
target_link_libraries(tetris_ui SFML::Graphics SFML::Window SFML::System SFML::Audio) 

target_include_directories(tetris_core PUBLIC core/include) 

add_executable(test_core tests/test_core_class.cpp)
target_link_libraries(test_core tetris_core Catch2::Catch2WithMain)

add_executable(tetris_game core/src/main.cpp ui/src/ui.cpp) 
target_link_libraries(tetris_game tetris_core tetris_ui SFML::Graphics SFML::Window SFML::System SFML::Audio) 



