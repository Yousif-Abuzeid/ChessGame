#include "ChessBoard.hpp" // Include the header file for the ChessBoard class to use its functionality
#include <string>        // Include the string library for string manipulation
#include <vector>       // Include the vector library for dynamic array functionality

/*
Main game loop function.
This function is responsible for managing the flow of the chess game,
including prompting players for moves and switching turns.
*/
void mainLoop();

/*
Function to determine whose turn it is to play.
Parameters:
    - counter: Reference to an integer that keeps track of the number of turns taken,
               which is used to determine the current player's turn.
    - isWhite: Boolean indicating whether the current turn belongs to the white player.
*/
void WhosTurn(int &counter, bool isWhite);

/*
Function to parse the player's move input from a string.
Parameters:
    - move: Reference to a string that contains the player's move in a specified format.
Returns:
    - A vector of integers representing the parsed move details,
      such as the starting and ending positions on the chessboard.
*/
std::vector<int> getMove(std::string & move);
