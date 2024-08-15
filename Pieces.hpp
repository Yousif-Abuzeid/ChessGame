#ifndef PIECES_HPP
#define PIECES_HPP 
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
    bool isAlive;
    PieceType type;

public:
    Piece(int r, int c, bool isWhite,PieceType); 
    virtual ~Piece() {} // Virtual destructor for proper cleanup
    virtual bool move(int r, int c,ChessBoard & board) = 0;
    virtual void display() const = 0;
    bool isWhitePiece() const;
    bool Alive() const;
    void setAlive(bool alive);
    PieceType GetType();
};


class Pawn : public Piece {
    private:
    bool FirstMove;
public:
    Pawn(int r, int c, bool isWhite) ;
    bool move(int r, int c,ChessBoard & board) override;
    void promotion();
    void display() const override ;
};

class Rook : public Piece {
public:
    Rook(int r, int c, bool isWhite) ;
    bool move(int r, int c,ChessBoard & board) override;
    void display() const override ;
};

class Knight : public Piece {
public:
    Knight(int r, int c, bool isWhite) ;
    bool move(int r, int c,ChessBoard & board) override;
    void display() const override ;
};


class Bishop : public Piece {
public:
    Bishop(int r, int c, bool isWhite);
    bool move(int r, int c,ChessBoard & board) override;
    void display() const override ;
};

class Queen : public Piece {
public:
    Queen(int r, int c, bool isWhite) ;
    bool move(int r, int c,ChessBoard & board) override;
    void display() const override ;
};

class King : public Piece {
private:
    bool isCheck;
public:
    King(int r, int c, bool isWhite);
    bool move(int r, int c,ChessBoard & board) override;
    void display() const override ;
    bool isCheckMate();
    bool isChecked();
    void CheckKing();
};


#endif // !PIECES_HPP
