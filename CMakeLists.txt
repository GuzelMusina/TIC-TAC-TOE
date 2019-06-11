cmake_minimum_required(VERSION 3.13)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 11)

add_executable(TicTacToe main.cpp Board.cpp Board.h Game.h Game.cpp Computer.cpp Computer.h)