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
    bool check(int r, int c, bool isWhite, bool ForAkill=false);
    bool checkMate(bool isWhite);\
    void killPiece(int r, int c);
};

#endif // !CHESS_BOARD_HPP