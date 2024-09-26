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
    /*
     *   Constructor
     *  Input: r:start row
     *         c: start column
     *         isWhite: Piece Color
     *            
    */
    Pawn(int r, int c, bool isWhite) ;
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
    bool move(int r, int c,ChessBoard & board) override;
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
    std::vector<Position> getValidMoves(ChessBoard & board) override;
    /*
        Overriden display method
    */
    void display() const override ;
};