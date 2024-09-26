#pragma once

#include <vector>
class ChessBoard; // Forward declaration

/*
*
*   Piece Types
*
*
*/
enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

/*
*
*   Class For Position Type
* 
*
*/
class Position {
private:
    int row;
    int col;
    
    
public:
    Position(int r , int c);
    int getRow() const ;
    int getCol() const ;
    bool isEquals(const Position& p) const ;
    void changePosition(int r, int c) ;
};

/*
*
*   Our Base Class For all Pieces
*
*
*/

class Piece {
protected:

    /*
        Common members for all pieces
    */
    Position pos;
    bool isWhite;
    PieceType type;

public:
    
    // Constructor
    Piece(int r, int c, bool isWhite,PieceType); 
    virtual ~Piece() {} // Virtual destructor for proper cleanup

    // pure virtual function to be overriden in inherited class
    // For movement of piece
    virtual bool move(int r, int c,ChessBoard & board) = 0;
    /*
            pure virtual function to be overriden in inherited class
            To display the piece

    */
    virtual void display() const = 0;
    /*
            pure virtual function to be overriden in inherited class
            To Get all valid moves for the piece

    */
    virtual std::vector<Position> getValidMoves(ChessBoard & board)=0;

    /*
        Method to get the color of piece
    */
    bool isWhitePiece() const;
    /*
        Method to get the type of piece 
    */
    PieceType GetType() const;

};

