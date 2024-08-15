#ifndef CHESS_BOARD_HPP
#include <vector>
#include "Pieces.hpp"
class ChessBoard {
private:
    std::vector<std::vector<Piece*>> board;
public:
    ChessBoard() ;
    
    ~ChessBoard() ;
    
    void display() const ;
    
    bool move(int r1, int c1, int r2, int c2);
    bool check(int r2, int c2, bool isWhite,PieceType type,int r1=-1,int c1=-1,bool forAkilling=false);
    bool checkMate(bool isWhite);
    void killPiece(int r, int c);
    friend bool CheckPawnMoveValid(int r,int c, ChessBoard& Board,bool iswhite,bool forAkilling);
    friend bool CheckRookMoveValid(int r1,int c1,int r2,int c2, ChessBoard& Board,bool iswhite);
    friend bool CheckKnightMoveValid(int r,int c, ChessBoard& Board,bool iswhite);
    friend bool CheckBishopMoveValid(int r,int c, ChessBoard& Board,bool iswhite);
    friend bool CheckQueenMoveValid(int r,int c, ChessBoard& Board,bool iswhite);
    friend bool CheckKingMoveValid(int r,int c, ChessBoard& Board,bool iswhite);


};

#endif // !CHESS_BOARD_HPP