#ifndef PIECES_HPP

class Position {
private:
    int row;
    int col;
public:
    Position(int r = 0, int c = 0) : row(r), col(c) {}
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
public:
    Piece(int r, int c, bool isWhite) : pos(r, c), isWhite(isWhite), isAlive(true) {}
    virtual ~Piece() {} // Virtual destructor for proper cleanup
    virtual bool move(int r, int c) = 0;
    virtual void display() const = 0;
    bool Alive() const;
    void setAlive(bool alive);
};


class Pawn : public Piece {
public:
    Pawn(int r, int c, bool isWhite) : Piece(r, c, isWhite) {}
    bool move(int r, int c) override;
    void display() const override ;
};

class Rook : public Piece {
public:
    Rook(int r, int c, bool isWhite) : Piece(r, c, isWhite) {}
    bool move(int r, int c) override;
    void display() const override ;
};

class Knight : public Piece {
public:
    Knight(int r, int c, bool isWhite) : Piece(r, c, isWhite) {}
    bool move(int r, int c) override;
    void display() const override ;
};


class Bishop : public Piece {
public:
    Bishop(int r, int c, bool isWhite) : Piece(r, c, isWhite) {}
    bool move(int r, int c) override;
    void display() const override ;
};

class Queen : public Piece {
public:
    Queen(int r, int c, bool isWhite) : Piece(r, c, isWhite) {}
    bool move(int r, int c) override;
    void display() const override ;
};

class King : public Piece {
private:
    bool isCheck;
public:
    King(int r, int c, bool isWhite) : Piece(r, c, isWhite), isCheck(false) {}
    bool move(int r, int c) override;
    void display() const override ;
    bool isCheckMate();
    bool isChecked();
};


#endif // !PIECES_HPP
