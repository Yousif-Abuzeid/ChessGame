#include "../lib/knight.hpp"       // Include the header file for the Knight class.
#include "../lib/ChessBoard.hpp"   // Include the header file for the ChessBoard class.
#include <iostream>

/*
 * ------------------------------------------------------------------------------------------------
 *   Knight Class Implementation
 * ------------------------------------------------------------------------------------------------
 */

/*
 * Constructor
 * 
 * Input:
 *   - r: Starting row position
 *   - c: Starting column position
 *   - isWhite: Boolean representing the color of the Knight (true for white, false for black)
 * 
 * Description:
 *   This constructor initializes a Knight by calling the base class (Piece) constructor
 *   and passing the specific PieceType as KNIGHT.
 */
Knight::Knight(int r, int c, bool isWhite) 
    : Piece(r, c, isWhite, PieceType::KNIGHT) {}

/*
 * move Method
 * 
 * Input:
 *   - r: The target row where the Knight intends to move
 *   - c: The target column where the Knight intends to move
 *   - board: Reference to the ChessBoard for validating the move
 * 
 * Output:
 *   - Returns true if the move is valid and executed, otherwise false
 * 
 * Description:
 *   This method checks if the Knight's move is valid. The Knight moves in an L-shape,
 *   meaning it can move two squares in one direction and one square perpendicular.
 *   The board's check method is called to ensure there are no obstructions in the path.
 */
bool Knight::move(int r, int c, ChessBoard &board) {
    /*
     * Retrieve the current position of the Knight.
     */
    int currentRow = pos.getRow();
    int currentCol = pos.getCol();

    /*
     * Knight moves in an L-shape: Check if the move is valid by confirming
     * that the move follows the knight's movement rules.
     */
    if ((abs(currentRow - r) == 2 && abs(currentCol - c) == 1) || 
        (abs(currentRow - r) == 1 && abs(currentCol - c) == 2)) {
        
        /*
         * Call board's check method to ensure there are no obstacles or
         * opposing pieces in the Knight's target position.
         */
        if (board.check(r, c, isWhite, GetType(), currentRow, currentCol)) {
            /*
             * If the move is valid, update the position of the Knight.
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
 *   This method displays the character representation of the Knight:
 *   'N' for a white Knight and 'n' for a black Knight.
 */
void Knight::display() const {
    std::cout << (isWhite ? "N" : "n");
}

/*
 * getValidMoves Method
 * 
 * Input:
 *   - board: Reference to the ChessBoard for checking valid move positions
 * 
 * Output:
 *   - Returns a vector of Position objects representing all valid moves for the Knight
 * 
 * Description:
 *   This method calculates all valid moves for the Knight by checking in all L-shaped directions.
 *   The board's check method is used to ensure the moves are valid, i.e., there are no
 *   pieces obstructing the path.
 */
std::vector<Position> Knight::getValidMoves(ChessBoard &board) {
    /*
     * Create a vector to store the valid moves for the Knight.
     */
    std::vector<Position> validMoves;

    /*
     * Get the current position of the Knight.
     */
    int currentRow = pos.getRow();
    int currentCol = pos.getCol();
    
    /*
     * Define all potential L-shaped moves for the Knight.
     */
    int potentialMoves[8][2] = {
        {currentRow + 2, currentCol + 1},  // Move: two up, one right
        {currentRow + 2, currentCol - 1},  // Move: two up, one left
        {currentRow - 2, currentCol + 1},  // Move: two down, one right
        {currentRow - 2, currentCol - 1},  // Move: two down, one left
        {currentRow + 1, currentCol + 2},  // Move: one up, two right
        {currentRow + 1, currentCol - 2},  // Move: one up, two left
        {currentRow - 1, currentCol + 2},  // Move: one down, two right
        {currentRow - 1, currentCol - 2}   // Move: one down, two left
    };

    /*
     * Check each potential move for validity.
     */
    for (const auto& move : potentialMoves) {
        int newRow = move[0];
        int newCol = move[1];
        
        // Verify the move is within board boundaries.
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            /*
             * Call the board's check method to verify if the target position is valid.
             */
            if (board.check(newRow, newCol, isWhite, GetType(), currentRow, currentCol)) {
                validMoves.push_back(Position(newRow, newCol)); // Add valid position to the list.
            }
        }
    }

    /*
     * Return the vector containing all valid move positions for the Knight.
     */
    return validMoves;
}
