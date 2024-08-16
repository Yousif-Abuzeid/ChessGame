#include "Pieces.hpp"
#include <iostream>
#include <cmath> // For std::abs
#include <vector>
#include "ChessBoard.hpp"

   
    /*
    Methods For Position Class
    */
    //constructor for Position class
    Position::Position(int r , int c) : row(r), col(c) {}
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
    //constructor for piece class
    Piece::Piece(int r, int c, bool isWhite ,PieceType type) : pos(r, c), isWhite(isWhite),type(type) {}

   
    bool Piece::isWhitePiece() const {
        return isWhite;
    }
    PieceType Piece::GetType(){
        return type;
    }
    
    /*
    Methods For Pawn Class
    */
    //constructor for pawn class
    Pawn::Pawn(int r, int c, bool isWhite) : Piece(r, c, isWhite,PieceType::PAWN),FirstMove(true) {}
    bool Pawn::move(int r, int c,ChessBoard & board) {
    // Check if the move is within the board and valid for the pawn's color
    // if (!board.check(r, c, isWhite,true)) {
    //     std::cout << "You Can't be in the same block with one of Your Pieces" << std::endl;
    //     return false;
    // }

    int currentRow = pos.getRow();
    int currentCol = pos.getCol();

    // First move can be two squares forward
    if (FirstMove && c == currentCol && abs(r - currentRow) == 2) {
         // Ensure no piece is blocking the move
        if(board.check(r, c, !isWhite,GetType())){
            pos.changePosition(r, c);
            FirstMove = false;
            return true;
        }
    }

    // Normal move: one square forward
    if (c == currentCol && r == currentRow + (isWhite ? 1 : -1)) {
            if(board.check(r, c, !isWhite,GetType())){
                pos.changePosition(r, c);
                return true;
            }
        
    }
    

    // Capture move: one square diagonally forward
    if ((abs(c - currentCol) == 1 && r == currentRow + (isWhite ? 1 : -1))&& board.check(r, c, isWhite ,GetType(),currentRow,currentCol,true)) {
        // Ensure there's an opponent piece to capture
        if(board.check(r, c, isWhite,GetType(),currentRow,currentCol,true)){   
            pos.changePosition(r, c);

            std::cout << "You Killed a Piece At (" << r << "," << c << ")" << std::endl;
            return true;
        }
        std::cout << "You Can't be in the same block with one of Your Pieces" << std::endl;
        }
    

    // If none of the valid move conditions are met, return false
    return false;
}

    void Pawn::display() const  {
        std::cout << (isWhite ? "P" : "p");
    }
    void Pawn::promotion(){
        

    }
    std::vector<Position> Pawn::getValidMoves(ChessBoard & board){
        std::vector<Position> validMoves;
        int currentRow = pos.getRow();
        int currentCol = pos.getCol();
        int forward = isWhite ? 1 : -1;

        // Check if the square in front of the pawn is empty
        if (board.check(currentRow + forward, currentCol, isWhite,GetType())) {
            validMoves.push_back(Position(currentRow + forward, currentCol));
        }

        // Check if the square two squares in front of the pawn is empty
        if (FirstMove && board.check(currentRow + 2 * forward, currentCol, isWhite,GetType())) {
            validMoves.push_back(Position(currentRow + 2 * forward, currentCol));
        }

        // Check if the pawn can capture an opponent piece
        if (board.check(currentRow + forward, currentCol + 1, isWhite,GetType())) {
            validMoves.push_back(Position(currentRow + forward, currentCol + 1));
        }
        if (board.check(currentRow + forward, currentCol - 1, isWhite,GetType())) {
            validMoves.push_back(Position(currentRow + forward, currentCol - 1));
        }

        return validMoves;
    }

    /*
    Methods For Rook Class
    */
    // constructor
    Rook::Rook(int r, int c, bool isWhite) : Piece(r, c, isWhite,PieceType::ROOK) {}
    bool Rook:: move(int r, int c,ChessBoard & board){
        /*
        Rook's Movement Logic
        */
        int currentRow=pos.getRow();
        int currentCol=pos.getCol();
        if(currentCol==c || currentRow == r){
            if(board.check(r,c, isWhite,GetType(),currentRow,currentCol)){
                pos.changePosition(r,c);
                return true;
            }
        }
        return false; 
        
    }
    void Rook::display() const {
        std::cout << (isWhite ? "R" : "r");
    }

    std::vector<Position> Rook::getValidMoves(ChessBoard&board){

    }


    /*
    Methods For Knight Class
    */
    //constructor
    Knight::Knight(int r, int c, bool isWhite) : Piece(r, c, isWhite,PieceType::KNIGHT) {}
    bool Knight::move(int r, int c,ChessBoard & board) {
        /*
        Knight's Movement Logic
        */
        int currentRow=pos.getRow();
        int currentCol=pos.getCol();
        
        if((abs(currentRow-r)==2 && abs(currentCol-c)==1) || (abs(currentRow-r)==1 && abs(currentCol-c)==2)){
            if(board.check(r,c, isWhite,GetType(),currentRow,currentCol)){
                pos.changePosition(r,c);
                return true;
            }
        }
    
        return false;
    }
    void Knight::display() const{
        std::cout << (isWhite ? "N" : "n");
    };

    std::vector<Position> Knight::getValidMoves(ChessBoard&board){

    }
    /*
    Methods For Bishop Class
    */
    //constructor
    Bishop::Bishop(int r, int c, bool isWhite) : Piece(r, c, isWhite,PieceType::BISHOP) {}
    bool Bishop:: move(int r, int c,ChessBoard & board) {
        /*
        Bishop's Movement Logic
        */
        int currentRow=pos.getRow();
        int currentCol=pos.getCol();

        if(abs(currentRow-r)==abs(currentCol-c)){
            if(board.check(r,c, isWhite,GetType(),currentRow,currentCol)){
                pos.changePosition(r,c);
                return true;
            }
        }
        return false;
    }
    void Bishop::display() const {
        std::cout << (isWhite ? "B" : "b");
    } 
    std::vector<Position> Bishop::getValidMoves(ChessBoard&board){

    }

    /*
    Methods For Queen Class
    */
    Queen::Queen(int r, int c, bool isWhite) : Piece(r, c, isWhite,PieceType::QUEEN) {}
    bool Queen:: move(int r, int c,ChessBoard & board) {
        /*
        Queen's Movement Logic
        */
        int currentRow=pos.getRow();
        int currentCol=pos.getCol();
        /*
        for rook movement
        */
        if(currentCol==c || currentRow == r){
            if(board.check(r,c, isWhite,GetType(),currentRow,currentCol)){
                pos.changePosition(r,c);
                return true;
            }
        }
        /*
        for bishop movement
        */
        if(abs(currentRow-r)==abs(currentCol-c)){
            if(board.check(r,c, isWhite,GetType(),currentRow,currentCol)){
                pos.changePosition(r,c);
                return true;
            }
        }
        return false;
    }
    void Queen::display() const {
        std::cout << (isWhite ? "Q" : "q");
    }
    std::vector<Position> Queen::getValidMoves(ChessBoard&board){

    }
    /*
    Methods For King Class
    */
    King::King(int r, int c, bool isWhite) : Piece(r, c, isWhite,PieceType::KING), isCheck(false) {}
    bool King::move(int r, int c,ChessBoard & board) {
        /*
        King's Movement Logic
        */
        return false;
    }
    void King::display() const{
        std::cout << (isWhite ? "K" : "k");
    }
    bool King::isCheckMate(){
        /*
        Logic
        */
        return false;
    }
    bool King::isChecked(){
        return isCheck;
    }
    void King::CheckKing(){
        isCheck=true;
    }
    std::vector<Position> King::getValidMoves(ChessBoard&board){

    }