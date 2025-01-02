// ChessBoard.hpp
#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include <QObject>
#include <QVector>
#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "king.hpp"

class ChessBoard : public QObject {
    Q_OBJECT

public:
    explicit ChessBoard(QObject *parent = nullptr);
    ~ChessBoard();

    // Board state
    QVector<QVector<Piece*>> board;

    // Qt-compatible move method
    Q_INVOKABLE bool move(int startRow, int startCol, int endRow, int endCol, bool isWhiteTurn);

    // Helper methods
    bool check(int r2, int c2, bool isWhite, PieceType type, int r1 = -1, int c1 = -1, bool forAkilling = false);
    bool checkMate(bool isWhite);
    bool CanBeKilled(int r, int c, bool isWhite);
    bool isSquareUnderAttack(int r, int c, bool isWhite);
    void killPiece(int r, int c);

signals:
    void boardUpdated();
    void checkOccurred(bool isWhiteInCheck);
    void checkMateOccurred(bool whiteWins);

private:
    bool isValidPosition(int row, int col) const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }

    bool isKingInCheck(bool isWhite);

    // Friend functions for move validation
    friend bool CheckPawnMoveValid(int r, int c, ChessBoard& Board, bool iswhite, bool forAkilling);
    friend bool CheckRookMoveValid(int r1, int c1, int r2, int c2, ChessBoard& Board, bool iswhite);
    friend bool CheckKnightMoveValid(int r1, int c1, int r2, int c2, ChessBoard& Board, bool iswhite);
    friend bool CheckBishopMoveValid(int r1, int c1, int r2, int c2, ChessBoard& Board, bool iswhite);
    friend bool CheckQueenMoveValid(int r1, int c1, int r2, int c2, ChessBoard& Board, bool iswhite);
    friend bool CheckKingMoveValid(int r, int c, ChessBoard& Board, bool iswhite);
};
#endif
