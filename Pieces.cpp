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
        if(!check(r,c,isWhite)){
            std::cout<<"invalid Move"<<std::endl;
            return false;
        }
        if(FirstMove && (c==pos.getCol()+2 &&pos.getRow()==r)){
            if(!check(r,c,!isWhite)){
            std::cout<<"invalid Move"<<std::endl;
            return false;
        }else{
            pos.changePosition(r, c);
        }
        }else if( c==pos.getCol()+1 && (pos.getRow()==r+1 ||pos.getRow()==r+1)){
            if(!check(r,c,!isWhite)){
                pos.changePosition(r, c);
                kill(r, c);
            std::cout<<"You Killed a Piece At ("<<r<<","<<c<<")"<<std::endl;
            return true;
        }else if(c==pos.getCol()+1 && pos.getRow()==r){
            pos.changePosition(r, c);
            return true;
        }
        }
        return false;
    }
    void Pawn::display() const  {
        std::cout << (isWhite ? "P" : "p");
    }
    void Pawn::promotion(){
        /*code*/
    }
    
