cmake_minimum_required(VERSION 3.25)
project(Cartography)

set(CMAKE_CXX_STANDARD 17)

add_executable(Cartography main.cpp feature.cpp feature.h button.cpp button.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include)
target_link_libraries(Cartography sfml-system sfml-window sfml-graphics sfml-audio)
