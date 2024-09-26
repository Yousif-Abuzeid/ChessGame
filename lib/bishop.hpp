#pragma once  // Ensure the file is included only once during compilation to avoid duplicate definitions
#include "basePiece.hpp"  // Include the base class for all chess pieces

/*
 * ------------------------------------------------------------------------------------------------
 *   Bishop Class Declaration
 * ------------------------------------------------------------------------------------------------
 *
 * This class represents the Bishop piece in the game of chess.
 * It inherits from the Piece class and defines specific behaviors for the Bishop,
 * including movement logic and displaying its shape on the board.
 */

class Bishop : public Piece {
public:
    /*
     * Constructor for the Bishop class
     * 
     * Input: 
     *   - r: The starting row position of the Bishop on the board
     *   - c: The starting column position of the Bishop on the board
     *   - isWhite: Boolean value indicating the color of the Bishop (true for white, false for black)
     * 
     * Description:
     *   This constructor initializes a Bishop piece by calling the base Piece constructor
     *   and passing the PieceType as BISHOP. The starting position and color are also set.
     */
    Bishop(int r, int c, bool isWhite);

    /*
     * move Method (Overrides Piece::move)
     * 
     * Input: 
     *   - r: The new row to which the Bishop is attempting to move
     *   - c: The new column to which the Bishop is attempting to move
     *   - board: Reference to the ChessBoard, used to check the validity of the move and other pieces on the board
     * 
     * Output:
     *   - Returns a boolean value indicating whether the move is valid (true) or not (false)
     * 
     * Description:
     *   This method overrides the move function from the Piece class. It contains the logic specific
     *   to the Bishop's movement, which allows diagonal movement across the board as long as the path is clear.
     */
    bool move(int r, int c, ChessBoard & board) override;

    /*
     * getValidMoves Method (Overrides Piece::getValidMoves)
     * 
     * Input:
     *   - board: Reference to the ChessBoard, used to check for valid move positions based on other pieces on the board
     * 
     * Output:
     *   - Returns a vector of Position objects, each representing a valid move that the Bishop can make from its current position
     * 
     * Description:
     *   This method provides a list of all valid moves the Bishop can make based on its current position.
     *   The Bishop can move diagonally in any direction as long as there are no other pieces blocking its path.
     */
    std::vector<Position> getValidMoves(ChessBoard & board) override;

    /*
     * display Method (Overrides Piece::display)
     * 
     * Input: None
     * 
     * Output: None
     * 
     * Description:
     *   This method displays the Bishop's representation on the board. The character displayed
     *   depends on the Bishop's color: 'B' for a white Bishop and 'b' for a black Bishop.
     *   This is useful for console-based board displays.
     */
    void display() const override;
};
