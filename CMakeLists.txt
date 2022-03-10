cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)


project(BATTLESHIP)

find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory(glfw)

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set(BATTLESHIP-SOURCE battleship-gui.cpp wagyourgui/GLFWSession.cpp wagyourgui/BaseElement.cpp wagyourgui/Font.cpp wagyourgui/Screen.cpp wagyourgui/Window.cpp)
add_executable(BATTLESHIP WIN32 ${BATTLESHIP-SOURCE})
target_link_libraries(BATTLESHIP ${OPENGL_LIBRARIES} glfw)

if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'BATTLESHIP' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BATTLESHIP )
    endif()
endif()