#include "Pieces.hpp"
//#include "ChessBoard.hpp"
#include <iostream>

    bool check(int r, int c, bool isWhite);
    void kill(int r,int c);
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
    Piece::Piece(int r, int c, bool isWhite) : pos(r, c), isWhite(isWhite), isAlive(true) {}
    bool Piece:: Alive() const{
        return isAlive;
    }
    void Piece::setAlive(bool alive){
        isAlive=alive;
    }
    /*
    Methods For Pawn Class
    */
    //constructor for pawn class
    Pawn::Pawn(int r, int c, bool isWhite) : Piece(r, c, isWhite),FirstMove(true) {}
    bool Pawn::move(int r, int c) {
    // Check if the move is within the board and valid for the pawn's color
    if (!check(r, c, isWhite)) {
        std::cout << "Invalid Move" << std::endl;
        return false;
    }

    int currentRow = pos.getRow();
    int currentCol = pos.getCol();

    // First move can be two squares forward
    if (FirstMove && c == currentCol && abs(r - currentRow) == 2) {
        if (!check(r, c, !isWhite)) { // Ensure no piece is blocking the move
            pos.changePosition(r, c);
            FirstMove = false;
            return true;
        } else {
            std::cout << "Invalid Move" << std::endl;
            return false;
        }
    }

    // Normal move: one square forward
    if (c == currentCol && r == currentRow + (isWhite ? 1 : -1)) {
        if (!check(r, c, !isWhite)) {
            pos.changePosition(r, c);
            return true;
        } else {
            std::cout << "Invalid Move" << std::endl;
            return false;
        }
    }

    // Capture move: one square diagonally forward
    if (abs(c - currentCol) == 1 && r == currentRow + (isWhite ? 1 : -1)) {
        if (check(r, c, !isWhite)) { // Ensure there's an opponent piece to capture
            pos.changePosition(r, c);
            kill(r, c);
            std::cout << "You Killed a Piece At (" << r << "," << c << ")" << std::endl;
            return true;
        } else {
            std::cout << "Invalid Move" << std::endl;
            return false;
        }
    }

    // If none of the valid move conditions are met, return false
    std::cout << "Invalid Move" << std::endl;
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
    bool Rook:: move(int r, int c){
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
    bool Knight::move(int r, int c) {
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
    bool Bishop:: move(int r, int c) {
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
    bool Queen:: move(int r, int c) {
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
    bool King::move(int r, int c) {
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