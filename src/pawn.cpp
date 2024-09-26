#include "../lib/pawn.hpp"
#include "../lib/ChessBoard.hpp"
#include <cmath>
#include <iostream>
#include <functional>

/*
* ------------------------------------------------------------------------------------------------
*   Pawn Class
* ------------------------------------------------------------------------------------------------
*
*   This class handles the behavior of the Pawn piece in the chess game. It includes methods for
*   moving, checking valid moves, and displaying the piece on the board.
*/

/*
 *   Constructor for Pawn
 *   Initializes a Pawn object with its starting row, column, and color.
 *  Input: r - the starting row of the pawn
 *         c - the starting column of the pawn
 *         isWhite - a boolean value representing whether the pawn is white (true) or black (false)
 *            
*/
Pawn::Pawn(int r, int c, bool isWhite) : Piece(r, c, isWhite, PieceType::PAWN), FirstMove(true) {}

/*
*   move Method
*   This method handles the movement of the pawn on the chessboard.
*   It checks if the move is valid according to the rules for pawn movement,
*   which includes moving forward one or two squares and capturing diagonally.
* 
* Input: r - the new row to move to
*        c - the new column to move to
*        board - a reference to the chessboard object, used to check other pieces' positions
*
* Output: Returns true if the move is valid and successfully made; otherwise, returns false.
*/
bool Pawn::move(int r, int c, ChessBoard & board) {

    // Get the current row and column of the pawn.
    int currentRow = pos.getRow();
    int currentCol = pos.getCol();

    /*
        Bind the `check` method from the ChessBoard class using `std::bind`.
        This creates a new callable function `enemyCheck` that automatically includes
        common parameters like `isWhite`, `GetType()`, `currentRow`, and `currentCol`.
        We only need to specify the row and column when calling `enemyCheck`.
    */
    auto enemyCheck = std::bind(&ChessBoard::check, &board, std::placeholders::_1, std::placeholders::_2, isWhite, GetType(), currentRow, currentCol, true);

    /*
        First Move Logic:
        If this is the pawn's first move and it's trying to move two squares forward,
        we check if the path is clear (no pieces blocking the way).
    */
    if (FirstMove && c == currentCol && abs(r - currentRow) == 2) {
        // If the path is clear (no blocking piece), update the position and mark FirstMove as false.
        if (board.check(r, c, !isWhite, GetType())) {
            pos.changePosition(r, c);  // Update the pawn's position to the new coordinates
            FirstMove = false;  // Mark that the pawn has made its first move
            return true;  // Move is successful
        }
    }

    /*
        Normal Forward Move:
        If the pawn is moving one square forward (which is the usual move),
        we again check that there are no pieces blocking the path.
    */
    if (c == currentCol && r == currentRow + (isWhite ? 1 : -1)) {
        // If no pieces are blocking, update the position and mark FirstMove as false.
        if (board.check(r, c, !isWhite, GetType())) {
            pos.changePosition(r, c);  // Update the position to the new row and column
            FirstMove = false;  // First move is now done
            return true;  // Move is valid
        }
    }

    /*
        Capture Move:
        If the pawn is attempting a diagonal move (to capture an opponent's piece),
        we use the `enemyCheck` function to ensure there's an opponent piece in the target position.
    */
    if (abs(c - currentCol) == 1 && r == currentRow + (isWhite ? 1 : -1)) {
        // If there is an opponent's piece to capture, update the position.
        if (enemyCheck(r, c)) {
            pos.changePosition(r, c);  // Update the pawn's position after capture
            return true;  // Capture move is valid
        }
    }

    // If no valid move was found, return false.
    return false;
}

/*
    display Method
    This method prints the shape of the pawn to the console.
    It displays 'P' for a white pawn and 'p' for a black pawn.
*/
void Pawn::display() const  {
    std::cout << (isWhite ? "P" : "p");  // Print "P" for white pawn, "p" for black pawn
}

void helper(int x, int y) {
    // Placeholder function (doesn't perform any action yet).
}

/*
*   getValidMoves Method
*   This method returns all valid moves for the pawn.
*   It checks the possible moves (forward and diagonal) and adds them to a vector.
*
* Input: board - reference to the chessboard, used for checking other pieces' positions
*
* Output: A vector containing all valid move positions for the pawn.
*/
std::vector<Position> Pawn::getValidMoves(ChessBoard & board) {
    // Create a vector to store all valid moves for the pawn
    std::vector<Position> validMoves;

    // Get the current position (row and column) of the pawn
    int currentRow = pos.getRow();
    int currentCol = pos.getCol();

    /*
        Determine the direction in which the pawn moves.
        White pawns move forward (increase row), black pawns move backward (decrease row).
    */
    int forward = isWhite ? 1 : -1;

    // Variables to store potential new row and column positions
    int newCol;
    int newRow;

    /*
        Check if the square directly in front of the pawn is empty.
        This is the normal move (one square forward).
    */
    newCol = currentCol;
    newRow = currentRow + forward;  // Move one square forward
    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
        // Check if the square is valid and not blocked
        if (board.check(newRow, newCol, isWhite, GetType())) {
            validMoves.push_back(Position(newRow, newCol));  // Add the move to the list
        }
    }

    /*
        Check if the square two squares in front of the pawn is empty.
        This move is only allowed on the pawn's first move.
    */
    newCol = currentCol;
    newRow = currentRow + 2 * forward;  // Move two squares forward
    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
        // Only allowed if it's the first move and the path is clear
        if (FirstMove && board.check(newRow, newCol, isWhite, GetType())) {
            validMoves.push_back(Position(newRow, newCol));  // Add the move to the list
        }
    }

    /*
        Check for possible capture moves (diagonal moves).
        Pawns capture pieces that are one square diagonally in front of them.
    */

    // Check the right diagonal (column + 1)
    newCol = currentCol + 1;
    newRow = currentRow + forward;  // Move one square forward diagonally
    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
        // Ensure there is an opponent's piece to capture in that position
        if (board.check(newRow, newCol, isWhite, GetType(), currentRow, currentCol, true)) {
            validMoves.push_back(Position(newRow, newCol));  // Add capture move
        }
    }

    // Check the left diagonal (column - 1)
    newCol = currentCol - 1;
    newRow = currentRow + forward;  // Move one square forward diagonally
    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
        // Ensure there is an opponent's piece to capture in that position
        if (board.check(newRow, newCol, isWhite, GetType(), currentRow, currentCol, true)) {
            validMoves.push_back(Position(newRow, newCol));  // Add capture move
        }
    }

    // Return the vector of valid moves
    return validMoves;
}
