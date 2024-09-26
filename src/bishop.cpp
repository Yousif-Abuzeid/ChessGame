#include "../lib/bishop.hpp"
#include "../lib/ChessBoard.hpp"
#include <iostream>

/*
 * ------------------------------------------------------------------------------------------------
 *   Bishop Class Implementation
 * ------------------------------------------------------------------------------------------------
 */

/*
 * Constructor
 * 
 * Input:
 *   - r: Starting row position
 *   - c: Starting column position
 *   - isWhite: Boolean representing the color of the Bishop (true for white, false for black)
 * 
 * Description:
 *   This constructor initializes a Bishop by calling the base class (Piece) constructor
 *   and passing the specific PieceType as BISHOP.
 */
Bishop::Bishop(int r, int c, bool isWhite) : Piece(r, c, isWhite, PieceType::BISHOP) {}

/*
 * move Method
 * 
 * Input:
 *   - r: The target row where the Bishop intends to move
 *   - c: The target column where the Bishop intends to move
 *   - board: Reference to the ChessBoard for validating the move
 * 
 * Output:
 *   - Returns true if the move is valid and executed, otherwise false
 * 
 * Description:
 *   This method checks if the Bishop's move is valid. The Bishop moves diagonally, meaning
 *   the change in row must equal the change in column. The board's check method is called 
 *   to ensure there is no obstruction in the path.
 */
bool Bishop::move(int r, int c, ChessBoard & board) {
    /*
     * Retrieve the current position of the Bishop.
     */
    int currentRow = pos.getRow();
    int currentCol = pos.getCol();

    /*
     * Bishop moves diagonally: Check if the absolute difference between
     * the current row and target row equals the absolute difference between
     * the current column and target column.
     */
    if (abs(currentRow - r) == abs(currentCol - c)) {
        /*
         * Call board's check method to ensure there are no obstacles or
         * opposing pieces in the Bishop's path.
         */
        if (board.check(r, c, isWhite, GetType(), currentRow, currentCol)) {
            /*
             * If the move is valid, update the position of the Bishop.
             */
            pos.changePosition(r, c);
            return true;  // The move was successful
        }
    }

    /*
     * If the move is invalid, return false.
     */
    return false;
}

/*
 * display Method
 * 
 * Input: None
 * Output: None
 * 
 * Description:
 *   This method displays the character representation of the Bishop:
 *   'B' for a white Bishop and 'b' for a black Bishop.
 */
void Bishop::display() const {
    std::cout << (isWhite ? "B" : "b");
}

/*
 * getValidMoves Method
 * 
 * Input:
 *   - board: Reference to the ChessBoard for checking valid move positions
 * 
 * Output:
 *   - Returns a vector of Position objects representing all valid moves for the Bishop
 * 
 * Description:
 *   This method calculates all valid moves for the Bishop by checking diagonally
 *   in all directions (forward-right, forward-left, backward-right, backward-left).
 *   The board's check method is used to ensure the moves are valid, i.e., there are no
 *   pieces obstructing the path.
 */
std::vector<Position> Bishop::getValidMoves(ChessBoard& board) {
    /*
     * Create a vector to store the valid moves for the Bishop.
     */
    std::vector<Position> validMoves;

    /*
     * Get the current position of the Bishop.
     */
    int currentRow = pos.getRow();
    int currentCol = pos.getCol();

    /*
     * Check for valid moves in the forward-right diagonal (moving towards increasing rows and columns).
     */
    for (int i = 1; currentRow + i < 8 && currentCol + i < 8; i++) {
        /*
         * Call the board's check method to verify if the target position is valid.
         */
        if (board.check(currentRow + i, currentCol + i, isWhite, GetType(), currentRow, currentCol)) {
            validMoves.push_back(Position(currentRow + i, currentCol + i));
        } else {
            break;  // Stop if a piece is blocking the path
        }
    }

    /*
     * Check for valid moves in the forward-left diagonal (moving towards increasing rows and decreasing columns).
     */
    for (int i = 1; currentRow + i < 8 && currentCol - i >= 0; i++) {
        if (board.check(currentRow + i, currentCol - i, isWhite, GetType(), currentRow, currentCol)) {
            validMoves.push_back(Position(currentRow + i, currentCol - i));
        } else {
            break;
        }
    }

    /*
     * Check for valid moves in the backward-right diagonal (moving towards decreasing rows and increasing columns).
     */
    for (int i = 1; currentRow - i >= 0 && currentCol + i < 8; i++) {
        if (board.check(currentRow - i, currentCol + i, isWhite, GetType(), currentRow, currentCol)) {
            validMoves.push_back(Position(currentRow - i, currentCol + i));
        } else {
            break;
        }
    }

    /*
     * Check for valid moves in the backward-left diagonal (moving towards decreasing rows and columns).
     */
    for (int i = 1; currentRow - i >= 0 && currentCol - i >= 0; i++) {
        if (board.check(currentRow - i, currentCol - i, isWhite, GetType(), currentRow, currentCol)) {
            validMoves.push_back(Position(currentRow - i, currentCol - i));
        } else {
            break;
        }
    }

    /*
     * Return the vector containing all valid move positions for the Bishop.
     */
    return validMoves;
}
