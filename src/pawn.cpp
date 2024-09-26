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
    *
    */
    /*
     *   Constructor
     *  Input: r:start row
     *         c: start column
     *         isWhite: Piece Color
     *            
    */
    Pawn::Pawn(int r, int c, bool isWhite) : Piece(r, c, isWhite,PieceType::PAWN),FirstMove(true) {}
    
    /*
    *
    * Name:   move Method
    * Description:  Method to move the pawn
    * Input: r:new row
    *        c:new column
    *        board: to get access to board and know other pieces positions
    *
    * Output: if the move is valid return true else false
    *
    *
   */
    bool Pawn::move(int r, int c, ChessBoard & board) {
    
    /*
        Get the current row and column
     */
    int currentRow = pos.getRow();
    int currentCol = pos.getCol();

    /*
        Bind check method from board with common parameters 
        except for row and column which will vary for each move
     */
    auto enemyCheck = std::bind(&ChessBoard::check, &board, std::placeholders::_1, std::placeholders::_2, isWhite, GetType(), currentRow, currentCol, true);

    /*
        Check if it's the first move 
        if true, it's possible to move 2 forward blocks
    */
    if (FirstMove && c == currentCol && abs(r - currentRow) == 2) {
         /*
            Call check method from board to check if there is a piece blocking the way
         */
        if (board.check(r, c, !isWhite, GetType())) {
            // Change the positions
            pos.changePosition(r, c);
            FirstMove = false;
            return true;
        }
    }

    /*
        Normal one forward block move
    */
    if (c == currentCol && r == currentRow + (isWhite ? 1 : -1)) {
            /*
                Call check method from board to check if there is a piece blocking the way
            */
            if (board.check(r, c, !isWhite, GetType())) {
                pos.changePosition(r, c);
                // Set FirstMove to false after the first move
                FirstMove = false;
                return true;
            }
    }

    /*
        Capture Move
    */
    if (abs(c - currentCol) == 1 && r == currentRow + (isWhite ? 1 : -1)) {
        /*
            Call boundCheck method from board to ensure there is an opponent piece in that position
        */
        if (enemyCheck(r, c)) {
            pos.changePosition(r, c);
            return true;
        }
    }

    /*
        There is no valid move, return false
    */
    return false;
}

    /*
        Method to display pawn shape
    */
    void Pawn::display() const  {
        std::cout << (isWhite ? "P" : "p");
    }

    
    void helper(int x, int y){

    }
     /*
    *
    * Name:   getValidMoves Method
    * Description:  Method to get the valid moves of the pawn
    * Input:
    *        board: to get access to board and know other pieces positions
    *
    * Output: Vector Containing the positions of valid moves for the pawn
    *
    *
   */
    std::vector<Position> Pawn::getValidMoves(ChessBoard & board) {
    // Create a vector to store all valid moves for the pawn
    std::vector<Position> validMoves;

    /*
        Get the current position (row and column) of the pawn.
        We need to evaluate moves relative to this position.
    */
    int currentRow = pos.getRow();
    int currentCol = pos.getCol();

    /*
        Determine the direction in which the pawn moves.
        If the pawn is white, it moves "up" the board (increasing row number).
        If the pawn is black, it moves "down" the board (decreasing row number).
    */
    int forward = isWhite ? 1 : -1;

    /*
        Variables to store the potential new row and column values for
        checking valid moves.
    */
    int newCol;
    int newRow;

    /*
        Check if the square directly in front of the pawn is empty:
        
        - The column remains the same (the pawn only moves forward in a straight line).
        - The row changes depending on the pawn's color (white or black).
        - Ensure the new position is within the board boundaries (0 to 7).
        - If the square is valid and empty, add it to the list of valid moves.
    */
    newCol = currentCol;
    newRow = currentRow + forward;  // Move forward one row
    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
        if (board.check(newRow, newCol, isWhite, GetType())) {
            validMoves.push_back(Position(newRow, newCol));  // Add valid move
        }
    }

    /*
        Check if the square two squares in front of the pawn is empty:
        
        - This move is only possible if the pawn is making its first move.
        - Similar to the previous check, but the row is two squares forward.
        - Check if the square is within the board boundaries and empty.
    */
    newCol = currentCol;
    newRow = currentRow + 2 * forward;  // Move forward two rows for first move
    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
        // The pawn can only move two squares if it is the first move
        if (FirstMove && board.check(newRow, newCol, isWhite, GetType())) {
            validMoves.push_back(Position(newRow, newCol));  // Add valid move
        }
    }

    /*
        Check if the pawn can capture an opponent piece:
        
        - Pawns capture diagonally, meaning the column changes by +1 or -1.
        - The row moves forward as usual.
        - We check both the right diagonal and left diagonal for an opponent's piece.
        - Ensure the diagonal positions are within the board boundaries.
    */

    // Check the right diagonal (column + 1)
    newCol = currentCol + 1;
    newRow = currentRow + forward;  // Move one row forward
    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
        /*
            Call the check method to ensure there is an opponent's piece in that position.
            The additional parameters (currentRow, currentCol, and `true`) are used for the capture logic.
        */
        if (board.check(newRow, newCol, isWhite, GetType(), currentRow, currentCol, true)) {
            validMoves.push_back(Position(newRow, newCol));  // Add valid move for capture
        }
    }

    // Check the left diagonal (column - 1)
    newCol = currentCol - 1;
    newRow = currentRow + forward;  // Move one row forward
    if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
        /*
            Similar to the right diagonal, call the check method for capturing an opponent's piece.
        */
        if (board.check(newRow, newCol, isWhite, GetType(), currentRow, currentCol, true)) {
            validMoves.push_back(Position(newRow, newCol));  // Add valid move for capture
        }
    }

    /*
        Return the list of valid moves.
        This could be a list of one or more valid positions, or an empty list if no valid moves are available.
    */
    return validMoves;
}
