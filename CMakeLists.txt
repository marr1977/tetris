cmake_minimum_required(VERSION 3.0.0)
project(Tetris VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Tetris Main.cpp TetrisBoard.cpp Tetromino.cpp TetrisBoardDrawer.cpp HighScores.cpp)

target_link_libraries(Tetris -lsfml-graphics)
target_link_libraries(Tetris -lsfml-window)
target_link_libraries(Tetris -lsfml-system)

configure_file(arial.ttf arial.ttf COPYONLY)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
