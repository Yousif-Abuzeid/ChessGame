#pragma once
#include "basePiece.hpp"


/*
    * ------------------------------------------------------------------------------------------------
    *   Pawn Class
    * ------------------------------------------------------------------------------------------------
    *
    *
    */
class Pawn : public Piece {
    private:
    /*
        bool to check fisrt move for double movement
    */
    bool FirstMove;
public:
    // Constructor
    Pawn(int r, int c, bool isWhite) ;
    /*
        Overriden move method
    */
    bool move(int r, int c,ChessBoard & board) override;
    /*
        Overriden valid moves method
    */
    std::vector<Position> getValidMoves(ChessBoard & board) override;
    /*
        Overriden display method
    */
    void display() const override ;
};