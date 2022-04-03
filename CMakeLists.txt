cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)

project(BATTLESHIP)

find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory(includes/glfw)

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
        src/battleship/screen2/WinLossScreen.h
        src/battleship/GameStateMachine.cpp src/battleship/GameStateMachine.h
        src/battleship/player2/BSOpponent2.cpp src/battleship/player2/BSOpponent2.h
        src/battleship/player2/BsPlayer2.cpp src/battleship/player2/BsPlayer2.h
        src/battleship/player2/BoardTracker.cpp src/battleship/player2/BoardTracker.h
        src/battleship/player2/BsBotOpponent.cpp src/battleship/player2/BsBotOpponent.h
        src/battleship/player2/BoardTrackerRenderer.cpp src/battleship/player2/BoardTrackerRenderer.h
        src/battleship/screen2/MainMenuScreen2.cpp src/battleship/screen2/MainMenuScreen2.h
        src/battleship/screen2/PlaceShipScreen2.cpp src/battleship/screen2/PlaceShipScreen2.h
        src/battleship/screen2/elements/BoardElement2.cpp src/battleship/screen2/elements/BoardElement2.h
        src/battleship/screen2/SyncOpponentScreen.cpp src/battleship/screen2/SyncOpponentScreen.h
        src/battleship/screen2/PlayScreen2.cpp src/battleship/screen2/PlayScreen2.h)

add_executable(BATTLESHIP WIN32 ${BATTLESHIP-SOURCE})
# allows not using ../ in #include, and specifying from the root of the project instead
target_include_directories(BATTLESHIP PUBLIC ./src ./includes)
target_link_libraries(BATTLESHIP ${OPENGL_LIBRARIES} glfw)

if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'BATTLESHIP' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BATTLESHIP )
    endif()
endif()