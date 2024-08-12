#include "Pieces.hpp"
#include <iostream>
#include <cmath> // For std::abs
#include "ChessBoard.hpp"

   
    /*
    Methods For Position Class
    */
    //constructor for Position class
    Position::Position(int r , int c) : row(r), col(c) {}
    int Position:: getRow() const { return row; }

    int Position::getCol() const { return col; }

    bool Position:: isEquals(const Position& p) const {
        return row == p.getRow() && col == p.getCol();;
    }
    void Position::changePosition(int r, int c){
        row = r;
        col = c;
    } ;

    /*
    Methods For Piece Class
    */
    //constructor for piece class
    Piece::Piece(int r, int c, bool isWhite ,bool isPawn=false) : pos(r, c), isWhite(isWhite), isAlive(true),pawn((isPawn)) {}

    bool Piece:: Alive() const{
        return isAlive;
    }
    void Piece::setAlive(bool alive){
        isAlive=alive;
    }
    bool Piece::isWhitePiece() const {
        return isWhite;
    }
    bool Piece::isPawn() const {
        return pawn;
    }
    /*
    Methods For Pawn Class
    */
    //constructor for pawn class
    Pawn::Pawn(int r, int c, bool isWhite) : Piece(r, c, isWhite,true),FirstMove(true) {}
    bool Pawn::move(int r, int c,ChessBoard & board) {
    // Check if the move is within the board and valid for the pawn's color
    // if (!board.check(r, c, isWhite,true)) {
    //     std::cout << "You Can't be in the same block with one of Your Pieces" << std::endl;
    //     return false;
    // }

    int currentRow = pos.getRow();
    int currentCol = pos.getCol();

    // First move can be two squares forward
    if (FirstMove && c == currentCol && abs(r - currentRow) == 2) {
         // Ensure no piece is blocking the move
        if(board.check(r, c, !isWhite)){
            pos.changePosition(r, c);
            FirstMove = false;
            return true;
        }
    }

    // Normal move: one square forward
    if (c == currentCol && r == currentRow + (isWhite ? 1 : -1)) {
            if(board.check(r, c, !isWhite)){
                pos.changePosition(r, c);
                return true;
            }
        
    }
    

    // Capture move: one square diagonally forward
    if ((abs(c - currentCol) == 1 && r == currentRow + (isWhite ? 1 : -1))&& board.check(r, c, isWhite ,true)) {
        // Ensure there's an opponent piece to capture
        if(board.check(r, c, isWhite, true)){   
            pos.changePosition(r, c);

            std::cout << "You Killed a Piece At (" << r << "," << c << ")" << std::endl;
            return true;
        }
        std::cout << "You Can't be in the same block with one of Your Pieces" << std::endl;
        }
    

    // If none of the valid move conditions are met, return false
    return false;
}

    void Pawn::display() const  {
        std::cout << (isWhite ? "P" : "p");
    }
    void Pawn::promotion(){
        /*code*/
    }

    /*
    Methods For Rook Class
    */
    // constructor
    Rook::Rook(int r, int c, bool isWhite) : Piece(r, c, isWhite) {}
    bool Rook:: move(int r, int c,ChessBoard & board){
        /*
        Rook's Movement Logic
        */
        return false; 
        
    }
    void Rook::display() const {
        std::cout << (isWhite ? "R" : "r");
    }


    /*
    Methods For Knight Class
    */
    //constructor
    Knight::Knight(int r, int c, bool isWhite) : Piece(r, c, isWhite) {}
    bool Knight::move(int r, int c,ChessBoard & board) {
        /*
        Knight's Movement Logic
        */
        return false;
    }
    void Knight::display() const{
        std::cout << (isWhite ? "N" : "n");
    };

    /*
    Methods For Bishop Class
    */
    //constructor
    Bishop::Bishop(int r, int c, bool isWhite) : Piece(r, c, isWhite) {}
    bool Bishop:: move(int r, int c,ChessBoard & board) {
        /*
        Bishop's Movement Logic
        */
        return false;
    }
    void Bishop::display() const {
        std::cout << (isWhite ? "B" : "b");
    } ;

    /*
    Methods For Queen Class
    */
    Queen::Queen(int r, int c, bool isWhite) : Piece(r, c, isWhite) {}
    bool Queen:: move(int r, int c,ChessBoard & board) {
        /*
        Queen's Movement Logic
        */
        return false;
    }
    void Queen::display() const {
        std::cout << (isWhite ? "Q" : "q");
    }
    /*
    Methods For King Class
    */
    King::King(int r, int c, bool isWhite) : Piece(r, c, isWhite), isCheck(false) {}
    bool King::move(int r, int c,ChessBoard & board) {
        /*
        King's Movement Logic
        */
        return false;
    }
    void King::display() const{
        std::cout << (isWhite ? "K" : "k");
    }
    bool King::isCheckMate(){
        /*
        Logic
        */
        return false;
    }
    bool King::isChecked(){
        return isCheck;
    }
    void King::CheckKing(){
        isCheck=true;
    }