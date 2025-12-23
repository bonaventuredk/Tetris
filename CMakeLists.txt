cmake_minimum_required(VERSION 3.28)
project(Tetrix)

set(CMAKE_CXX_STANDARD 17)

# Path to libraries if not found automatically

list(APPEND CMAKE_PREFIX_PATH "C:/Program\ Files\ (x86)/Library/C++/Catch2")
list(APPEND CMAKE_PREFIX_PATH "C:/Program\ Files/Library/C++/SFML-3.0.2")


set(SFML_STATIC_LIBRARIES ON) # for linux 

find_package(Catch2 3 REQUIRED)
find_package(SFML 3 COMPONENTS Graphics Audio REQUIRED)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System) 

include_directories(core/include ui/include)
add_library(tetrix_core core/src/core_class.cpp)
add_library(tetrix_ui ui/src/ui.cpp)
target_link_libraries(tetrix_ui SFML::Graphics SFML::Window SFML::System SFML::Audio) 

target_include_directories(tetrix_core PUBLIC core/include) # for linux : Vraiment nécessaire ? : Oui, sinon tetrix_game ne voit pas les headers du core(en tout cas chez moi).


add_executable(test_core tests/test_core_class.cpp)
target_link_libraries(test_core tetrix_core Catch2::Catch2WithMain)

add_executable(tetrix_game core/src/main.cpp) 
target_link_libraries(tetrix_game tetrix_core tetrix_ui SFML::Graphics SFML::Window SFML::System SFML::Audio) 





