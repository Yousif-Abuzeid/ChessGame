#include "Pieces.hpp"
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
    
