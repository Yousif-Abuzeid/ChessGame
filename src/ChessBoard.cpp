#include "../lib/ChessBoard.hpp"

#include <iostream>
#include <ostream>

/*
Constructor For the Board
*/
// Implementation in ChessBoard.cpp
ChessBoard::ChessBoard(QObject *parent) : QObject(parent) {
    // Initialize empty board
    board.resize(8);
    for (int i = 0; i < 8; ++i) {
        board[i].resize(8, nullptr);
    }

    // Set up pieces
    for (int i = 0; i < 8; i++) {
        board[1][i] = new Pawn(1, i, true);
        board[6][i] = new Pawn(6, i, false);
    }

    // White pieces
    board[0][0] = new Rook(0, 0, true);
    board[0][7] = new Rook(0, 7, true);
    board[0][1] = new Knight(0, 1, true);
    board[0][6] = new Knight(0, 6, true);
    board[0][2] = new Bishop(0, 2, true);
    board[0][5] = new Bishop(0, 5, true);
    board[0][3] = new Queen(0, 3, true);
    board[0][4] = new King(0, 4, true);

    // Black pieces
    board[7][0] = new Rook(7, 0, false);
    board[7][7] = new Rook(7, 7, false);
    board[7][1] = new Knight(7, 1, false);
    board[7][6] = new Knight(7, 6, false);
    board[7][2] = new Bishop(7, 2, false);
    board[7][5] = new Bishop(7, 5, false);
    board[7][3] = new Queen(7, 3, false);
    board[7][4] = new King(7, 4, false);
}

ChessBoard::~ChessBoard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete board[i][j];
        }
    }
}



bool ChessBoard::move(int startRow, int startCol, int endRow, int endCol, bool isWhiteTurn) {
    // Validate positions
    if (!isValidPosition(startRow, startCol) || !isValidPosition(endRow, endCol)) {
        return false;
    }

    // Check if there's a piece to move
    if (!board[startRow][startCol]) {
        return false;
    }

    // Verify piece color matches turn
    if (board[startRow][startCol]->isWhitePiece() != isWhiteTurn) {
        return false;
    }

    // Cannot capture king
    if (board[endRow][endCol] && board[endRow][endCol]->GetType() == PieceType::KING) {
        return false;
    }

    // Store captured piece for potential move reversal
    Piece* capturedPiece = board[endRow][endCol];

    // Attempt move
    if (board[startRow][startCol]->move(endRow, endCol, *this)) {
        // Execute move
        board[endRow][endCol] = board[startRow][startCol];
        board[startRow][startCol] = nullptr;

        // Check if move puts own king in check
        if (isKingInCheck(isWhiteTurn)) {
            // Undo move
            board[startRow][startCol] = board[endRow][endCol];
            board[endRow][endCol] = capturedPiece;
            return false;
        }

        // Check opponent's king status
        bool opponentInCheck = isKingInCheck(!isWhiteTurn);
        if (opponentInCheck) {
            emit checkOccurred(!isWhiteTurn);
            if (checkMate(!isWhiteTurn)) {
                emit checkMateOccurred(isWhiteTurn);
            }
        }

        delete capturedPiece;
        emit boardUpdated();
        return true;
    }

    return false;
}

void ChessBoard::killPiece(int r, int c) {
    if (isValidPosition(r, c) && board[r][c]) {
        delete board[r][c];
        board[r][c] = nullptr;
        emit boardUpdated();
    }
}
/*
Check Pawn Move Valid
*/
bool CheckPawnMoveValid(int r,int c,ChessBoard& Board,bool isWhite,bool forAkilling=false){
    if(forAkilling){

        if (Board.board[r][c] != nullptr && Board.board[r][c]->isWhitePiece() != isWhite){
            return true;
        }
    }else{
    if(Board.board[r][c] == nullptr){
        return true;
    }

    if(Board.board[r][c] != nullptr && Board.board[r][c]->isWhitePiece() == isWhite){
        return false;
    }


    return false;
}
    return false;

}
/*
Check Rook Move Valid
*/
bool CheckRookMoveValid(int r1,int c1,int r2,int c2, ChessBoard& Board,bool iswhite){
    if(r1 == r2){
        for(int i = c1 + 1; i < c2; i++){
            if(Board.board[r1][i] != nullptr){
                return false;
            }
        }
        if(Board.board[r2][c2] != nullptr && Board.board[r2][c2]->isWhitePiece() == iswhite){
            return false;
        }
        return true;
    }
    if(c1 == c2){
        for(int i = r1 + 1; i < r2; i++){
            if(Board.board[i][c1] != nullptr){
                return false;
            }
        }
        if(Board.board[r2][c2] != nullptr && Board.board[r2][c2]->isWhitePiece() == iswhite){
            return false;
        }
        return true;
    }
    return false;
}
/*
Check Bishop Move Valid
*/
bool CheckBoolMoveValid(int r1,int c1,int r2,int c2, ChessBoard& Board,bool iswhite){
    if(abs(r1 - r2) == abs(c1 - c2)){
        int row = r1 < r2 ? r1 + 1 : r1 - 1;
        int col = c1 < c2 ? c1 + 1 : c1 - 1;
        while(row != r2 && col != c2){
            if(Board.board[row][col] != nullptr){
                return false;
            }
            row = r1 < r2 ? row + 1 : row - 1;
            col = c1 < c2 ? col + 1 : col - 1;
        }
        if(Board.board[r2][c2] != nullptr && Board.board[r2][c2]->isWhitePiece() == iswhite){
            return false;
        }
        return true;
    }
    return false;
}
/*
Check Knight Move Valid
*/
bool CheckKnightMoveValid(int r1,int c1,int r2,int c2, ChessBoard& Board,bool iswhite){
    if((abs(r1 - r2) == 2 && abs(c1 - c2) == 1) || (abs(r1 - r2) == 1 && abs(c1 - c2) == 2)){
        if(Board.board[r2][c2] != nullptr && Board.board[r2][c2]->isWhitePiece() == iswhite){
            return false;
        }
        return true;
    }
    return false;
}
/*
Check Queen Move Valid
*/
bool CheckQueenMoveValid(int r1,int c1,int r2,int c2, ChessBoard& Board,bool iswhite){
    if(CheckBoolMoveValid(r1, c1, r2, c2, Board, iswhite) || CheckRookMoveValid(r1, c1, r2, c2, Board, iswhite)){
        return true;
    }
    return false;
}

bool CheckKingMoveValid(int r1, int c1, int r2, int c2, ChessBoard& Board, bool iswhite) {
    if (abs(r2 - r1) <= 1 && abs(c2 - c1) <= 1) {
        // Check if the target square is not occupied by a friendly piece
        if (Board.board[r2][c2] == nullptr || Board.board[r2][c2]->isWhitePiece() != iswhite) {
            // Check if the target square is under attack
            if (!Board.isSquareUnderAttack(r2, c2, iswhite)) {
                return true;
            }
        }
    }
    return false;
}

bool ChessBoard::isSquareUnderAttack(int r, int c, bool isWhite) {
    // Iterate through all opponent's pieces and check if they can attack the square
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr && board[i][j]->isWhitePiece() != isWhite) {
                std::vector<Position> validMoves = board[i][j]->getValidMoves(*this);
                for (const Position& pos : validMoves) {
                    if (pos.getRow() == r && pos.getCol() == c) {
                        return true; // Square is under attack
                    }
                }
            }
        }
    }
    return false; // Square is safe
}

/*
check function
*/
bool ChessBoard::check(int r2,int c2, bool isWhite,PieceType type,int r1, int c1,bool forAkilling){
   switch (type) {
   case PieceType::PAWN:
    if(CheckPawnMoveValid(r2, c2, *this, isWhite,forAkilling)){
        return true;
    }
   break;
   case PieceType::ROOK:
   if(CheckRookMoveValid(r1, c1,r2,c2,*this,isWhite)){
       return true;
   }
   case PieceType::BISHOP:
   if(CheckBoolMoveValid(r1, c1,r2,c2,*this,isWhite)){
       return true;
   }
   case PieceType::KNIGHT:
    if(CheckKnightMoveValid(r1, c1,r2,c2,*this,isWhite)){
         return true;
    }
   case PieceType::QUEEN:
    if(CheckQueenMoveValid(r1, c1,r2,c2,*this,isWhite)){
        return true;
    }
   case PieceType::KING:
      //if (CheckKingMoveValid(r1, c1, r2, c2, *this, isWhite)) {
           return true;
       //}
    default:
        break;
   }
   return false;
}

/*
Check if the
*/


bool ChessBoard::CanBeKilled(int r, int c,bool isWhite){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] != nullptr && board[i][j]->isWhitePiece() != isWhite){
                std::vector<Position> validMoves = board[i][j]->getValidMoves(*this);
                for(int k = 0; k < validMoves.size(); k++){
                    if(validMoves[k].getRow() == r && validMoves[k].getCol() == c){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// Add these methods to ChessBoard.cpp

bool ChessBoard::isKingInCheck(bool isWhite) {
    // Find king's position
    int kingRow = -1, kingCol = -1;

    // Search for the king of the specified color
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] &&
                board[i][j]->GetType() == PieceType::KING &&
                board[i][j]->isWhitePiece() == isWhite) {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
        if (kingRow != -1) break;
    }

    // Check if any opponent's piece can capture the king
    return CanBeKilled(kingRow, kingCol, isWhite);
}

bool ChessBoard::checkMate(bool isWhite) {
    // If not in check, can't be checkmate
    if (!isKingInCheck(isWhite)) {
        return false;
    }

    // Find king's position
    int kingRow = -1, kingCol = -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] &&
                board[i][j]->GetType() == PieceType::KING &&
                board[i][j]->isWhitePiece() == isWhite) {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
        if (kingRow != -1) break;
    }

    // Check all pieces of the same color to see if any move can prevent check
    for (int startRow = 0; startRow < 8; startRow++) {
        for (int startCol = 0; startCol < 8; startCol++) {
            if (board[startRow][startCol] &&
                board[startRow][startCol]->isWhitePiece() == isWhite) {

                // Get all valid moves for this piece
                std::vector<Position> validMoves = board[startRow][startCol]->getValidMoves(*this);

                // Try each move
                for (const Position& pos : validMoves) {
                    int endRow = pos.getRow();
                    int endCol = pos.getCol();

                    // Store the piece that might be captured
                    Piece* capturedPiece = board[endRow][endCol];

                    // Make the move temporarily
                    Piece* movingPiece = board[startRow][startCol];
                    board[endRow][endCol] = movingPiece;
                    board[startRow][startCol] = nullptr;

                    // Check if the king is still in check
                    bool stillInCheck = isKingInCheck(isWhite);

                    // Undo the move
                    board[startRow][startCol] = movingPiece;
                    board[endRow][endCol] = capturedPiece;

                    // If any move takes the king out of check, it's not checkmate
                    if (!stillInCheck) {
                        return false;
                    }
                }
            }
        }
    }

    // If we've tried all moves and none prevent check, it's checkmate
    return true;
}

