#ifndef PIECES_HPP
#define PIECES_HPP 
#include <vector>
class ChessBoard; // Forward declaration

enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
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

class Piece {
protected:
    Position pos;
    bool isWhite;
    
    PieceType type;

public:
    Piece(int r, int c, bool isWhite,PieceType); 
    virtual ~Piece() {} // Virtual destructor for proper cleanup
    virtual bool move(int r, int c,ChessBoard & board) = 0;
    virtual void display() const = 0;
    virtual std::vector<Position> getValidMoves(ChessBoard & board)=0;

    bool isWhitePiece() const;
    
    PieceType GetType();
};


class Pawn : public Piece {
    private:
    bool FirstMove;
public:
    Pawn(int r, int c, bool isWhite) ;
    bool move(int r, int c,ChessBoard & board) override;
    std::vector<Position> getValidMoves(ChessBoard & board) override;
    void promotion();
    void display() const override ;
};

class Rook : public Piece {
public:
    Rook(int r, int c, bool isWhite) ;
    bool move(int r, int c,ChessBoard & board) override;
    std::vector<Position> getValidMoves(ChessBoard & board) override;
    void display() const override ;
};

class Knight : public Piece {
public:
    Knight(int r, int c, bool isWhite) ;
    bool move(int r, int c,ChessBoard & board) override;
    std::vector<Position> getValidMoves(ChessBoard & board) override;
    void display() const override ;
};


class Bishop : public Piece {
public:
    Bishop(int r, int c, bool isWhite);
    bool move(int r, int c,ChessBoard & board) override;
    std::vector<Position> getValidMoves(ChessBoard & board) override;
    void display() const override ;
};

class Queen : public Piece {
public:
    Queen(int r, int c, bool isWhite) ;
    bool move(int r, int c,ChessBoard & board) override;
    std::vector<Position> getValidMoves(ChessBoard & board) override;
    void display() const override ;
};

class King : public Piece {
private:
    bool isCheck;
    Position CheckingPiece;
public:
    King(int r, int c, bool isWhite);
    bool move(int r, int c,ChessBoard & board) override;
    std::vector<Position> getValidMoves(ChessBoard & board) override;
    void display() const override ;
    bool isCheckMate(ChessBoard&board);
    bool isChecked();
    void CheckKing(Position p);
};


#endif // !PIECES_HPP
