#include "../lib/king.hpp"            // Include the header file for the King class.
#include "../lib/ChessBoard.hpp"      // Include the header file for the ChessBoard class.
#include <iostream>                   // Include the iostream library for console output.


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
 *   It also initializes the isCheck state to false, indicating that the
 *   King is not currently in check, and sets the CheckingPiece to an
 *   invalid position (0, 0).
 */
King::King(int r, int c, bool isWhite) 
    : Piece(r, c, isWhite, PieceType::KING), 
      isCheck(false), 
      CheckingPiece(0, 0) {}

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
 *   This method checks if the King's move is valid. The King can move one square
 *   in any direction (horizontally, vertically, or diagonally). The board's check 
 *   method is called to ensure the move does not result in a check.
 */
bool King::move(int r, int c, ChessBoard & board) {
    int currentRow = pos.getRow();       // Get the current row of the King.
    int currentCol = pos.getCol();       // Get the current column of the King.

    // Check if the target position is within one square distance.
    if (abs(currentRow - r) <= 1 && abs(currentCol - c) <= 1) {
        // Check if the move is valid according to the ChessBoard rules.
        if (board.check(r, c, isWhite, GetType(), currentRow, currentCol)) {
            pos.changePosition(r, c);     // Update the King's position.
            return true;                  // Move executed successfully.
        }
    }
    return false;                         // Move is invalid.
}

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
void King::display() const {
    std::cout << (isWhite ? "K" : "k");  // Output the corresponding character based on the King's color.
}

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
bool King::isCheckMate(ChessBoard& board) {
    if (isCheck) {                       // Check if the King is currently in check.
        std::vector<Position> validMoves = getValidMoves(board); // Get all valid moves.
        if (validMoves.size() == 0) {    // If there are no valid moves, it's checkmate.
            return true;
        }
    }
    return false;                       // The King is not in checkmate.
}

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
bool King::isChecked() {
    return isCheck;                     // Return the current state of isCheck.
}

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
void King::CheckKing(Position p) {
    isCheck = true;                    // Set isCheck to true, indicating the King is in check.
    CheckingPiece = p;                // Update the position of the checking piece.
}

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
std::vector<Position> King::getValidMoves(ChessBoard& board) {
    std::vector<Position> validMoves;    // Vector to store valid moves.
    int currentRow = pos.getRow();       // Get the current row of the King.
    int currentCol = pos.getCol();       // Get the current column of the King.

    // Check for valid moves in the forward direction
    if (board.check(currentRow + 1, currentCol, isWhite, GetType(), currentRow, currentCol)) {
        validMoves.push_back(Position(currentRow + 1, currentCol)); // Move forward
    }
    if (board.check(currentRow + 1, currentCol + 1, isWhite, GetType(), currentRow, currentCol)) {
        validMoves.push_back(Position(currentRow + 1, currentCol + 1)); // Move forward right
    }
    if (board.check(currentRow + 1, currentCol - 1, isWhite, GetType(), currentRow, currentCol)) {
        validMoves.push_back(Position(currentRow + 1, currentCol - 1)); // Move forward left
    }

    // Check for valid moves in the backward direction
    if (board.check(currentRow - 1, currentCol, isWhite, GetType(), currentRow, currentCol)) {
        validMoves.push_back(Position(currentRow - 1, currentCol)); // Move backward
    }
    if (board.check(currentRow - 1, currentCol + 1, isWhite, GetType(), currentRow, currentCol)) {
        validMoves.push_back(Position(currentRow - 1, currentCol + 1)); // Move backward right
    }
    if (board.check(currentRow - 1, currentCol - 1, isWhite, GetType(), currentRow, currentCol)) {
        validMoves.push_back(Position(currentRow - 1, currentCol - 1)); // Move backward left
    }

    // Check for valid moves in the right direction
    if (board.check(currentRow, currentCol + 1, isWhite, GetType(), currentRow, currentCol)) {
        validMoves.push_back(Position(currentRow, currentCol + 1)); // Move right
    }

    // Check for valid moves in the left direction
    if (board.check(currentRow, currentCol - 1, isWhite, GetType(), currentRow, currentCol)) {
        validMoves.push_back(Position(currentRow, currentCol - 1)); // Move left
    }

    return validMoves;                 // Return the vector of valid moves.
}
