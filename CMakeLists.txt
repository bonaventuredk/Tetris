cmake_minimum_required(VERSION 3.10)
project(Tetrix)

set(CMAKE_CXX_STANDARD 17)

if(FALSE)
find_package(Catch2 3 REQUIRED)
find_package(SFML REQUIRED)
endif()

include_directories(core/include)
add_library(tetrix_core core/src/core_class.cpp)

add_executable(Tetrix_test core/include/test_core_class.cpp)
target_link_libraries(Tetrix_test tetrix_core)

if(FALSE)
target_link_libraries(test_core_class tetrix_core Catch2WithMain)
endif()
