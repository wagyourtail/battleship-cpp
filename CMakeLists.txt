cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)


project(BATTLESHIP)

find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory(glfw)

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set(BATTLESHIP-SOURCE
        main.cpp
        wagyourgui/GLFWSession.cpp
        wagyourgui/elements/BaseElement.cpp
        wagyourgui/Font.cpp
        wagyourgui/Screen.cpp
        wagyourgui/Window.cpp
        wagyourgui/DrawableHelper.cpp
        wagyourgui/GLBuilder.cpp
        wagyourgui/Texture.cpp
        wagyourgui/elements/Button.cpp
        wagyourgui/elements/DisableableElement.cpp
        battleship/Battleship.cpp
        battleship/BSBot.cpp
        battleship/BSLocal.cpp
        battleship/BSOpponent.cpp
        battleship/BSPlayer.cpp
        battleship/BSPlayerGui.cpp
        battleship/GameSession.cpp
        battleship/NoGuiRunner.cpp
        battleship/screen/MainMenuScreen.cpp
        battleship/screen/PlaceShipsScreen.cpp
        battleship/screen/elements/BoardElement.cpp
        battleship/screen/PlayScreen.cpp
        battleship/screen/WinLossScreen.h)
add_executable(BATTLESHIP WIN32 ${BATTLESHIP-SOURCE})
# allows not using ../ in #include, and specifying from the root of the project instead
target_include_directories(BATTLESHIP PUBLIC ./)
target_link_libraries(BATTLESHIP ${OPENGL_LIBRARIES} glfw)

if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'BATTLESHIP' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BATTLESHIP )
    endif()
endif()