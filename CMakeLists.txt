cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)

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
        src/client/main.cpp
        src/client/wagyourgui/GLFWSession.cpp src/client/wagyourgui/GLFWSession.h
        src/client/wagyourgui/elements/BaseElement.cpp src/client/wagyourgui/elements/BaseElement.h
        src/client/wagyourgui/Font.cpp src/client/wagyourgui/Font.h
        src/client/wagyourgui/Screen.cpp src/client/wagyourgui/Screen.h
        src/client/wagyourgui/Window.cpp src/client/wagyourgui/Window.h
        src/client/wagyourgui/DrawableHelper.cpp src/client/wagyourgui/DrawableHelper.h
        src/client/wagyourgui/GLBuilder.cpp src/client/wagyourgui/GLBuilder.h
        src/client/wagyourgui/Texture.cpp src/client/wagyourgui/Texture.h
        src/client/wagyourgui/elements/Button.cpp src/client/wagyourgui/elements/Button.h
        src/client/wagyourgui/elements/DisableableElement.cpp src/client/wagyourgui/elements/DisableableElement.h
        src/client/battleship/Battleship.cpp src/client/battleship/Battleship.h
        src/client/battleship/screen/WinLossScreen.h
        src/client/battleship/GameStateMachine.cpp src/client/battleship/GameStateMachine.h
        src/client/battleship/player/BSOpponent.cpp src/client/battleship/player/BSOpponent.h
        src/client/battleship/player/BsPlayer.cpp src/client/battleship/player/BsPlayer.h
        src/client/battleship/player/BoardTracker.cpp src/client/battleship/player/BoardTracker.h
        src/client/battleship/player/BsBotOpponent.cpp src/client/battleship/player/BsBotOpponent.h
        src/client/battleship/player/BoardTrackerRenderer.cpp src/client/battleship/player/BoardTrackerRenderer.h
        src/client/battleship/screen/MainMenuScreen.cpp src/client/battleship/screen/MainMenuScreen.h
        src/client/battleship/screen/PlaceShipScreen.cpp src/client/battleship/screen/PlaceShipScreen.h
        src/client/battleship/screen/elements/BoardElement.cpp src/client/battleship/screen/elements/BoardElement.h
        src/client/battleship/screen/SyncOpponentScreen.cpp src/client/battleship/screen/SyncOpponentScreen.h
        src/client/battleship/screen/PlayScreen.cpp src/client/battleship/screen/PlayScreen.h
        src/client/battleship/player/RemoteOpponent.cpp src/client/battleship/player/RemoteOpponent.h
        src/client/battleship/screen/MultiplayerScreen.cpp src/client/battleship/screen/MultiplayerScreen.h
        src/shared/SocketConnection.cpp src/shared/SocketConnection.h src/client/wagyourgui/elements/TextInput.cpp src/client/wagyourgui/elements/TextInput.h src/client/battleship/screen/ConnectingScreen.cpp src/client/battleship/screen/ConnectingScreen.h)

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

project(BATTLESHIP-SERVER)
add_executable(BATTLESHIP-SERVER src/server/main.cpp
        src/server/Session.cpp src/server/Session.h
        src/shared/SocketConnection.cpp src/shared/SocketConnection.h)
target_include_directories(BATTLESHIP-SERVER PUBLIC ./src)