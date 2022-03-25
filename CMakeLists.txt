cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)

project(BATTLESHIP)

find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set ( SOCKPP_BUILD_STATIC ON )

add_subdirectory(includes/glfw)
add_subdirectory(includes/sockpp)

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set(BATTLESHIP-SOURCE
        src/main.cpp
        src/wagyourgui/GLFWSession.cpp
        src/wagyourgui/elements/BaseElement.cpp
        src/wagyourgui/Font.cpp
        src/wagyourgui/Screen.cpp
        src/wagyourgui/Window.cpp
        src/wagyourgui/DrawableHelper.cpp
        src/wagyourgui/GLBuilder.cpp
        src/wagyourgui/Texture.cpp
        src/wagyourgui/elements/Button.cpp
        src/wagyourgui/elements/DisableableElement.cpp
        src/battleship/Battleship.cpp
        src/battleship/BSBot.cpp
        src/battleship/BSLocal.cpp
        src/battleship/BSOpponent.cpp
        src/battleship/BSPlayer.cpp
        src/battleship/BSPlayerGui.cpp
        src/battleship/GameSession.cpp
        src/battleship/NoGuiRunner.cpp
        src/battleship/screen/MainMenuScreen.cpp
        src/battleship/screen/PlaceShipsScreen.cpp
        src/battleship/screen/elements/BoardElement.cpp
        src/battleship/screen/PlayScreen.cpp
        src/battleship/screen/WinLossScreen.h)
add_executable(BATTLESHIP WIN32 ${BATTLESHIP-SOURCE})
# allows not using ../ in #include, and specifying from the root of the project instead
target_include_directories(BATTLESHIP PUBLIC ./src ./includes)
target_link_libraries(BATTLESHIP ${OPENGL_LIBRARIES} glfw sockpp)

if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'BATTLESHIP' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BATTLESHIP )
    endif()
endif()