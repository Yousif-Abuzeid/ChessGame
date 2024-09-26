#ifndef CHESS_BOARD_HPP  // Include guard to prevent multiple inclusions of this header file.
#define CHESS_BOARD_HPP

#include <vector>
#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "king.hpp"

// Class representing the chessboard in the game.
class ChessBoard {
private:
    std::vector<std::vector<Piece*>> board;  // 2D vector representing the chessboard, holding pointers to Piece objects.

public:
    /*
     * Constructor
     * 
     * Description:
     *   Initializes the chessboard and sets up the initial configuration of pieces.
     */
    ChessBoard();

    /*
     * Destructor
     * 
     * Description:
     *   Cleans up and deallocates memory used for pieces on the board.
     */
    ~ChessBoard();

    /*
     * display Method
     * 
     * Input: None
     * Output: None
     * 
     * Description:
     *   Displays the current state of the chessboard to the console.
     */
    void display() const;

    /*
     * move Method
     * 
     * Input:
     *   - r1: Starting row index of the piece to move
     *   - c1: Starting column index of the piece to move
     *   - r2: Target row index where the piece intends to move
     *   - c2: Target column index where the piece intends to move
     *   - isWhite: Boolean indicating the color of the piece (true for white, false for black)
     * 
     * Output:
     *   - Returns true if the move was successful, otherwise false
     * 
     * Description:
     *   Attempts to move a piece from its starting position to the target position.
     *   Validates the move based on chess rules and the current state of the board.
     */
    bool move(int r1, int c1, int r2, int c2, bool isWhite);

    /*
     * check Method
     * 
     * Input:
     *   - r2: Target row index for checking conditions
     *   - c2: Target column index for checking conditions
     *   - isWhite: Boolean indicating the color of the piece
     *   - type: Type of the piece attempting the move
     *   - r1: (Optional) Starting row index of the piece (default is -1)
     *   - c1: (Optional) Starting column index of the piece (default is -1)
     *   - forAkilling: (Optional) Boolean flag indicating if the check is for a capture move
     * 
     * Output:
     *   - Returns true if the move does not result in a check situation for the king
     * 
     * Description:
     *   Validates if a move to a specified position is legal without placing the king in check.
     */
    bool check(int r2, int c2, bool isWhite, PieceType type, int r1 = -1, int c1 = -1, bool forAkilling = false);

    /*
     * checkMate Method
     * 
     * Input:
     *   - isWhite: Boolean indicating the color of the king to check for checkmate
     * 
     * Output:
     *   - Returns true if the king of the specified color is in checkmate
     * 
     * Description:
     *   Determines if the king of the specified color is in checkmate.
     */
    bool checkMate(bool isWhite);

    /*
     * killPiece Method
     * 
     * Input:
     *   - r: Row index of the piece to be killed
     *   - c: Column index of the piece to be killed
     * 
     * Output: None
     * 
     * Description:
     *   Removes a piece from the board at the specified position.
     */
    void killPiece(int r, int c);

    /*
     * CanBeKilled Method
     * 
     * Input:
     *   - r: Row index of the piece to check
     *   - c: Column index of the piece to check
     *   - isWhite: Boolean indicating the color of the piece
     * 
     * Output:
     *   - Returns true if the piece at the specified position can be captured
     * 
     * Description:
     *   Checks if a piece of the specified color can be captured at a given position.
     */
    bool CanBeKilled(int r, int c, bool isWhite);

    // Friend function declarations for piece-specific move validation.
    friend bool CheckPawnMoveValid(int r, int c, ChessBoard& Board, bool iswhite, bool forAkilling);
    friend bool CheckRookMoveValid(int r1, int c1, int r2, int c2, ChessBoard& Board, bool iswhite);
    friend bool CheckKnightMoveValid(int r1, int c1, int r2, int c2, ChessBoard& Board, bool iswhite);
    friend bool CheckBoolMoveValid(int r1, int c1, int r2, int c2, ChessBoard& Board, bool iswhite);
    friend bool CheckQueenMoveValid(int r1, int c1, int r2, int c2, ChessBoard& Board, bool iswhite);
    friend bool CheckKingMoveValid(int r, int c, ChessBoard& Board, bool iswhite);
};

#endif // !CHESS_BOARD_HPP
