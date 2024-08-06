#include "Pieces.hpp"
#include "ChessBoard.hpp"
#include <iostream>

    bool check(int r, int c, bool isWhite);
    void kill(int r,int c);
    /*
    Methods For Position Class
    */
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
    bool Piece:: Alive() const{
        return isAlive;
    }
    void Piece::setAlive(bool alive){
        isAlive=alive;
    }
    /*
    Methods For Pawn Class
    */
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

