#include "../lib/queen.hpp"
#include "../lib/ChessBoard.hpp"
#include <iostream>

/*
 * ------------------------------------------------------------------------------------------------
 *   Queen Class Implementation
 * ------------------------------------------------------------------------------------------------
 */

/*
 * Constructor
 * 
 * Input:
 *   - r: Starting row position of the Queen on the chessboard
 *   - c: Starting column position of the Queen on the chessboard
 *   - isWhite: Boolean representing the color of the Queen (true for white, false for black)
 * 
 * Description:
 *   This constructor initializes a Queen by calling the base class
 *   (Piece) constructor and passing the specific PieceType as QUEEN.
 */
Queen::Queen(int r, int c, bool isWhite) : Piece(r, c, isWhite, PieceType::QUEEN) {}

/*
 * move Method
 * 
 * Input:
 *   - r: The target row where the Queen intends to move
 *   - c: The target column where the Queen intends to move
 *   - board: Reference to the ChessBoard for validating the move
 * 
 * Output:
 *   - Returns true if the move is valid and executed, otherwise false
 * 
 * Description:
 *   This method checks if the Queen's move is valid. The Queen can move
 *   either like a Rook (horizontally or vertically) or like a Bishop
 *   (diagonally). The board's check method is called to ensure there are
 *   no obstructions in the path.
 */
bool Queen::move(int r, int c, ChessBoard & board) {
    /*
     * Retrieve the current position of the Queen.
     */
    int currentRow = pos.getRow();
    int currentCol = pos.getCol();

    /*
     * Check for Rook-like movement (horizontal or vertical).
     */
    if (currentCol == c || currentRow == r) {
        if (board.check(r, c, isWhite, GetType(), currentRow, currentCol)) {
            pos.changePosition(r, c);
            return true; // The move was successful
        }
    }

    /*
     * Check for Bishop-like movement (diagonal).
     */
    if (abs(currentRow - r) == abs(currentCol - c)) {
        if (board.check(r, c, isWhite, GetType(), currentRow, currentCol)) {
            pos.changePosition(r, c);
            return true; // The move was successful
        }
    }

    return false; // Move is invalid
}

/*
 * display Method
 * 
 * Input: None
 * Output: None
 * 
 * Description:
 *   This method displays the character representation of the Queen:
 *   'Q' for a white Queen and 'q' for a black Queen.
 */
void Queen::display() const {
    std::cout << (isWhite ? "Q" : "q");
}

/*
 * getValidMoves Method
 * 
 * Input:
 *   - board: Reference to the ChessBoard for checking valid move positions
 * 
 * Output:
 *   - Returns a vector of Position objects representing all valid moves for the Queen
 * 
 * Description:
 *   This method calculates all valid moves for the Queen by checking 
 *   in all possible directions (horizontal, vertical, and diagonal).
 *   The board's check method is used to ensure the moves are valid, 
 *   i.e., there are no pieces obstructing the path.
 */
std::vector<Position> Queen::getValidMoves(ChessBoard & board) {
    std::vector<Position> validMoves; // Vector to store valid moves
    int currentRow = pos.getRow();    // Current row of the Queen
    int currentCol = pos.getCol();    // Current column of the Queen

    // Check for valid moves in the forward direction
    for (int i = currentRow + 1; i < 8; i++) {
        if (board.check(i, currentCol, isWhite, GetType(), currentRow, currentCol)) {
            validMoves.push_back(Position(i, currentCol));
        } else {
            break; // Stop if a piece is blocking the path
        }
    }

    // Check for valid moves in the backward direction
    for (int i = currentRow - 1; i >= 0; i--) {
        if (board.check(i, currentCol, isWhite, GetType(), currentRow, currentCol)) {
            validMoves.push_back(Position(i, currentCol));
        } else {
            break; // Stop if a piece is blocking the path
        }
    }

    // Check for valid moves in the right direction
    for (int i = currentCol + 1; i < 8; i++) {
        if (board.check(currentRow, i, isWhite, GetType(), currentRow, currentCol)) {
            validMoves.push_back(Position(currentRow, i));
        } else {
            break; // Stop if a piece is blocking the path
        }
    }

    // Check for valid moves in the left direction
    for (int i = currentCol - 1; i >= 0; i--) {
        if (board.check(currentRow, i, isWhite, GetType(), currentRow, currentCol)) {
            validMoves.push_back(Position(currentRow, i));
        } else {
            break; // Stop if a piece is blocking the path
        }
    }

    // Check for valid moves in the forward right diagonal
    for (int i = 1; currentRow + i < 8 && currentCol + i < 8; i++) {
        if (board.check(currentRow + i, currentCol + i, isWhite, GetType(), currentRow, currentCol)) {
            validMoves.push_back(Position(currentRow + i, currentCol + i));
        } else {
            break; // Stop if a piece is blocking the path
        }
    }

    // Check for valid moves in the forward left diagonal
    for (int i = 1; currentRow + i < 8 && currentCol - i >= 0; i++) {
        if (board.check(currentRow + i, currentCol - i, isWhite, GetType(), currentRow, currentCol)) {
            validMoves.push_back(Position(currentRow + i, currentCol - i));
        } else {
            break; // Stop if a piece is blocking the path
        }
    }

    // Check for valid moves in the backward right diagonal
    for (int i = 1; currentRow - i >= 0 && currentCol + i < 8; i++) {
        if (board.check(currentRow - i, currentCol + i, isWhite, GetType(), currentRow, currentCol)) {
            validMoves.push_back(Position(currentRow - i, currentCol + i));
        } else {
            break; // Stop if a piece is blocking the path
        }
    }

    // Check for valid moves in the backward left diagonal
    for (int i = 1; currentRow - i >= 0 && currentCol - i >= 0; i++) {
        if (board.check(currentRow - i, currentCol - i, isWhite, GetType(), currentRow, currentCol)) {
            validMoves.push_back(Position(currentRow - i, currentCol - i));
        } else {
            break; // Stop if a piece is blocking the path
        }
    }

    return validMoves; // Return the vector containing all valid move positions for the Queen
}
