#include "../lib/rook.hpp" // Include the header file for the Rook class
#include "../lib/ChessBoard.hpp" // Include the ChessBoard class for board operations
#include <iostream> // Include iostream for displaying the Rook's shape


/*
    * ------------------------------------------------------------------------------------------------
    *   Rook Class Implementation
    * ------------------------------------------------------------------------------------------------
    * The Rook class is a derived class from the Piece base class. It handles the Rook piece's
    * movement logic, how it interacts with the board, and how it displays itself on the board.
    */

    /*
     *   Constructor: Rook
     *   This constructor initializes the Rook object with the given row, column, and piece color.
     *   It passes these values to the base Piece class constructor along with the type of piece (ROOK).
     *   
     *   Input: 
     *         r: Start row (integer representing the row position of the rook)
     *         c: Start column (integer representing the column position of the rook)
     *         isWhite: Piece color (boolean representing if the rook is white or black)
     */
    Rook::Rook(int r, int c, bool isWhite) : Piece(r, c, isWhite, PieceType::ROOK) {}

    /*
     *   move Method
     *   Description: This method is responsible for moving the rook on the chessboard. 
     *                The rook can move any number of squares along the same row or column.
     *
     *   Input:
     *         r: New row (integer representing the destination row on the board)
     *         c: New column (integer representing the destination column on the board)
     *         board: A reference to the ChessBoard object, used to check the validity of the move
     *
     *   Output:
     *         Returns true if the move is valid, and false otherwise.
     *
     */
    bool Rook::move(int r, int c, ChessBoard & board) {
        /*
         * Get the current row and column of the rook's position.
         * The rook's current position is retrieved using the pos object, which is of type Position.
         */
        int currentRow = pos.getRow(); // Get the current row position of the rook
        int currentCol = pos.getCol(); // Get the current column position of the rook
        
        /*
         * Check if the rook's move is either along the same column (vertical move) 
         * or along the same row (horizontal move).
         * The rook moves either horizontally or vertically, so one of these conditions must be true.
         */
        if (currentCol == c || currentRow == r) { // If moving in the same row or column
            /*
             * Call the board's check method to ensure the destination square (r, c) is valid.
             * The check method verifies if the move is legal and if there are no pieces blocking the path.
             * If the check passes, the rook's position is updated to (r, c), and the method returns true.
             */
            if (board.check(r, c, isWhite, GetType(), currentRow, currentCol)) {
                pos.changePosition(r, c); // Change the rook's position to the new row and column
                return true; // Move is valid
            }
        }
        /*
         * If the move is not valid (i.e., the rook is trying to move diagonally or to an invalid position),
         * the method returns false.
         */
        return false; // Move is invalid
    }

    /*
     *   display Method
     *   This method displays the rook's shape (character representation) on the console.
     *   The display shows 'R' for a white rook and 'r' for a black rook.
     *   Output:
     *         Displays the character corresponding to the rook's color.
     */
    void Rook::display() const {
        /*
         * Output 'R' for a white rook and 'r' for a black rook.
         * The isWhite boolean determines which character is displayed.
         */
        std::cout << (isWhite ? "R" : "r");
    }

    /*
     *   getValidMoves Method
     *   Description: This method returns a list of all valid moves for the rook based on its current position.
     *                The rook moves horizontally or vertically on the chessboard.
     *
     *   Input:
     *         board: A reference to the ChessBoard object, which provides information about the state of the board.
     *
     *   Output:
     *         Returns a vector of Position objects, each representing a valid move for the rook.
     */
    std::vector<Position> Rook::getValidMoves(ChessBoard & board) {
        // Create a vector to store the valid moves for the rook.
        std::vector<Position> validMoves;

        // Get the current row and column of the rook.
        int currentRow = pos.getRow(); // Rook's current row position
        int currentCol = pos.getCol(); // Rook's current column position

        /*
         * Check for valid moves in the forward direction (along the same column, increasing row index).
         * The rook can move to any unoccupied square or capture an opponent's piece in this direction.
         */
        for (int i = currentRow + 1; i < 8; i++) { // Iterate through rows above the current row
            if (board.check(i, currentCol, isWhite, GetType())) { // Check if the move is valid
                validMoves.push_back(Position(i, currentCol)); // Add the valid move to the list
            } else {
                break; // Stop if an obstacle is encountered (a piece is blocking the rook's path)
            }
        }

        /*
         * Check for valid moves in the backward direction (along the same column, decreasing row index).
         * The rook can move to any unoccupied square or capture an opponent's piece in this direction.
         */
        for (int i = currentRow - 1; i >= 0; i--) { // Iterate through rows below the current row
            if (board.check(i, currentCol, isWhite, GetType())) { // Check if the move is valid
                validMoves.push_back(Position(i, currentCol)); // Add the valid move to the list
            } else {
                break; // Stop if an obstacle is encountered
            }
        }

        /*
         * Check for valid moves in the right direction (along the same row, increasing column index).
         * The rook can move to any unoccupied square or capture an opponent's piece in this direction.
         */
        for (int i = currentCol + 1; i < 8; i++) { // Iterate through columns to the right of the current column
            if (board.check(currentRow, i, isWhite, GetType())) { // Check if the move is valid
                validMoves.push_back(Position(currentRow, i)); // Add the valid move to the list
            } else {
                break; // Stop if an obstacle is encountered
            }
        }

        /*
         * Check for valid moves in the left direction (along the same row, decreasing column index).
         * The rook can move to any unoccupied square or capture an opponent's piece in this direction.
         */
        for (int i = currentCol - 1; i >= 0; i--) { // Iterate through columns to the left of the current column
            if (board.check(currentRow, i, isWhite, GetType())) { // Check if the move is valid
                validMoves.push_back(Position(currentRow, i)); // Add the valid move to the list
            } else {
                break; // Stop if an obstacle is encountered
            }
        }

        /*
         * Return the vector of valid moves for the rook.
         * The vector contains all the valid moves the rook can make from its current position.
         */
        return validMoves;
    }
