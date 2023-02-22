cmake_minimum_required(VERSION 3.21)
project(BombIT LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.x)
FetchContent_MakeAvailable(SFML)

set(SOURCES
	main.cpp
	Screen.h
	Screen.cpp
	Animation.h
	Animation.cpp
	Block.h
	Block.cpp
	Bomb.h
	Bomb.cpp
	Obstacle.h
	Obstacle.cpp
	Pav.h
	Pav.cpp
	Player.h
	Player.cpp
	PLAYER_ANIM.h
	Screen.h
	Screen.cpp
	Solid.h
	Solid.cpp
)
add_executable(BombIT ${SOURCES})
target_link_libraries(BombIT PRIVATE sfml-graphics)
target_compile_features(BombIT PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET BombIT POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:BombIT> $<TARGET_FILE_DIR:BombIT> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS BombIT)