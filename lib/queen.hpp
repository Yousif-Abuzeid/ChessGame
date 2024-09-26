#pragma once               // Ensure this header file is included only once during compilation.
#include "basePiece.hpp"   // Include the base class header file for Piece.

 /*
 * ------------------------------------------------------------------------------------------------
 *   Queen Class Definition
 * ------------------------------------------------------------------------------------------------
 */

 /*
 * Queen Class
 * 
 * Description:
 *   The Queen class represents the chess piece known as the Queen.
 *   The Queen is a powerful piece that can move any number of squares
 *   in any direction: horizontally, vertically, or diagonally.
 */
class Queen : public Piece {
public:
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
    Queen(int r, int c, bool isWhite);

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
     *   This method checks if the Queen's move is valid. The Queen moves
     *   in straight lines (horizontally or vertically) or diagonally.
     *   The board's check method is called to ensure there are no 
     *   obstructions in the path.
     */
    bool move(int r, int c, ChessBoard & board) override;

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
    std::vector<Position> getValidMoves(ChessBoard & board) override;

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
    void display() const override;
};
