#pragma once
#include "basePiece.hpp"

/*
 * ------------------------------------------------------------------------------------------------
 *   Knight Class Declaration
 * ------------------------------------------------------------------------------------------------
 * 
 * The Knight class represents a knight piece in chess. Inherits from the Piece base class.
 * This class handles the specific movement, display, and valid move generation for the Knight.
 */
class Knight : public Piece {
public:
    /*
     * Constructor
     * 
     * Input:
     *   - r: Initial row position of the knight
     *   - c: Initial column position of the knight
     *   - isWhite: Boolean to indicate if the knight is white (true) or black (false)
     * 
     * Description:
     *   The constructor initializes the Knight object with its starting position and color, 
     *   and sets its type to KNIGHT by calling the base class constructor.
     */
    Knight(int r, int c, bool isWhite);

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
     *   Implements the knight's "L" shaped movement. The knight moves in an "L" shape,
     *   meaning it moves two squares in one direction (horizontal or vertical) and one 
     *   square perpendicular to that direction. This method also checks if the move is valid
     *   using the ChessBoard's check method.
     */
    bool move(int r, int c, ChessBoard & board) override;

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
     *   This method calculates all valid moves for the knight based on its "L" shaped movement.
     *   It considers both the movement rules and any obstacles on the board (other pieces).
     */
    std::vector<Position> getValidMoves(ChessBoard & board) override;

    /*
     * display Method
     * 
     * Input: None
     * Output: None
     * 
     * Description:
     *   This method displays the character representation of the Knight:
     *   'N' for a white knight and 'n' for a black knight.
     */
    void display() const override;
};
