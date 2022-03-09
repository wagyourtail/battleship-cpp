cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(glfw)

project(WYG)
add_executable(WYG wagyourgui/wagyourgui.h wagyourgui/wagyourgui.cpp)

project(BATTLESHIP)
add_executable(BATTLESHIP stb/stb_truetype.h battleship-nogui.h battleship-nogui.cpp battleship-gui.h battleship-gui.cpp)