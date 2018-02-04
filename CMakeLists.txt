cmake_minimum_required(VERSION 3.8)
project(ProjektZC)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES  2graczy.c main.c 2graczy.h 3graczy.h 3graczy.c 4graczy.c 4graczy.h types.h zmianyNotacjiIObrazow.c zmianyNotacjiIObrazow.h WspolneFunkcjeRoznchWersji.c WspolneFunkcjeRoznchWersji.h sprawdzaniePrzesuniec.c sprawdzaniePrzesuniec.h )
add_executable(ProjektZC ${SOURCE_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(ProjektZC ${GTK3_LIBRARIES})