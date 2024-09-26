cmake_minimum_required(VERSION 3.22)
project(ChessGame)
add_executable(ChessGame main.cpp src/ChessBoard.cpp src/pawn.cpp src/rook.cpp src/knight.cpp src/bishop.cpp src/queen.cpp src/king.cpp src/basePiece.cpp src/App.cpp)
