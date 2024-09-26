#pragma once                          // Ensure this header file is included only once during compilation.
#include "basePiece.hpp"              // Include the base class header file for Piece.

/*
 * ------------------------------------------------------------------------------------------------
 *   King Class Definition
 * ------------------------------------------------------------------------------------------------
 */

/*
 * King Class
 * 
 * Description:
 *   The King class represents the chess piece known as the King.
 *   The King is a crucial piece in chess; the objective of the game is to checkmate the opponent's King.
 *   The King can move one square in any direction: horizontally, vertically, or diagonally.
 */
class King : public Piece {
private:
    bool isCheck;                     // Boolean indicating whether the King is in check.
    Position CheckingPiece;           // Position of the piece that is currently checking the King.

public:
    /*
     * Constructor
     * 
     * Input:
     *   - r: Starting row position of the King on the chessboard
     *   - c: Starting column position of the King on the chessboard
     *   - isWhite: Boolean representing the color of the King (true for white, false for black)
     * 
     * Description:
     *   This constructor initializes a King by calling the base class
     *   (Piece) constructor and passing the specific PieceType as KING.
     */
    King(int r, int c, bool isWhite);

    /*
     * move Method
     * 
     * Input:
     *   - r: The target row where the King intends to move
     *   - c: The target column where the King intends to move
     *   - board: Reference to the ChessBoard for validating the move
     * 
     * Output:
     *   - Returns true if the move is valid and executed, otherwise false
     * 
     * Description:
     *   This method checks if the King's move is valid. The King moves
     *   one square in any direction. The board's check method is called 
     *   to ensure there are no obstructions in the path and that the King
     *   does not move into check.
     */
    bool move(int r, int c, ChessBoard & board) override;

    /*
     * getValidMoves Method
     * 
     * Input:
     *   - board: Reference to the ChessBoard for checking valid move positions
     * 
     * Output:
     *   - Returns a vector of Position objects representing all valid moves for the King
     * 
     * Description:
     *   This method calculates all valid moves for the King by checking 
     *   one square in all possible directions (horizontally, vertically, 
     *   and diagonally). The board's check method is used to ensure the moves
     *   are valid, i.e., they do not place the King in check.
     */
    std::vector<Position> getValidMoves(ChessBoard & board) override;

    /*
     * display Method
     * 
     * Input: None
     * Output: None
     * 
     * Description:
     *   This method displays the character representation of the King:
     *   'K' for a white King and 'k' for a black King.
     */
    void display() const override;

    /*
     * isCheckMate Method
     * 
     * Input:
     *   - board: Reference to the ChessBoard to check for checkmate conditions
     * 
     * Output:
     *   - Returns true if the King is in checkmate, otherwise false
     * 
     * Description:
     *   This method checks if the King is in checkmate by evaluating 
     *   all possible moves. If there are no valid moves available 
     *   that would get the King out of check, it returns true.
     */
    bool isCheckMate(ChessBoard& board);

    /*
     * isChecked Method
     * 
     * Input: None
     * Output: None
     * 
     * Description:
     *   This method checks if the King is currently in check. 
     *   It returns true if the King is in check, otherwise false.
     */
    bool isChecked();

    /*
     * CheckKing Method
     * 
     * Input:
     *   - p: Position of the piece checking the King
     * 
     * Output: None
     * 
     * Description:
     *   This method updates the CheckingPiece position when the King is 
     *   in check, allowing the King to track which piece is threatening it.
     */
    void CheckKing(Position p);
};
