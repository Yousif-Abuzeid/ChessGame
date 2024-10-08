#include "../lib/Pieces.hpp"
#include <iostream>
#include <cmath> // For std::abs
#include <vector>
#include "../lib/ChessBoard.hpp"

   
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
        int newCol ;
        int newRow ;

        // Check if the square in front of the pawn is empty
        newCol = currentCol;
        newRow = currentRow + forward;
        if(newRow>=0 && newRow<8 && newCol>=0 && newCol<8){
            if (board.check(newRow, newCol, isWhite,GetType())) {
                validMoves.push_back(Position(newRow, newCol));
            }
        }

        // Check if the square two squares in front of the pawn is empty
        newCol = currentCol;
        newRow = currentRow + 2 * forward;
        if(newRow>=0 && newRow<8 && newCol>=0 && newCol<8){
            if (FirstMove && board.check(newRow, newCol, isWhite,GetType())) {
                validMoves.push_back(Position(newRow, newCol));
            }
        }
        

        // Check if the pawn can capture an opponent piece

        newCol = currentCol + 1;
        newRow = currentRow + forward;
        if(newRow>=0 && newRow<8 && newCol>=0 && newCol<8){
            if (board.check(newRow, newCol, isWhite,GetType(),currentRow,currentCol),true) {
                validMoves.push_back(Position(newRow, newCol));
            }
        }
        
        newCol = currentCol - 1;
        newRow = currentRow + forward;

        if(newRow>=0 && newRow<8 && newCol>=0 && newCol<8){
            if (board.check(newRow, newCol, isWhite,GetType(),currentRow,currentCol),true) {
                validMoves.push_back(Position(newRow, newCol));
            }
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
        std::vector<Position> validMoves;
        int currentRow = pos.getRow();
        int currentCol = pos.getCol();

        // Check for valid moves in the forward direction
        for (int i = currentRow + 1; i < 8; i++) {
            if (board.check(i, currentCol, isWhite,GetType())) {
                validMoves.push_back(Position(i, currentCol));
            } else {
                break;
            }
        }

        // Check for valid moves in the backward direction
        for (int i = currentRow - 1; i >= 0; i--) {
            if (board.check(i, currentCol, isWhite,GetType())) {
                validMoves.push_back(Position(i, currentCol));
            } else {
                break;
            }
        }

        // Check for valid moves in the right direction

        for (int i = currentCol + 1; i < 8; i++) {
            if (board.check(currentRow, i, isWhite,GetType())) {
                validMoves.push_back(Position(currentRow, i));
            } else {
                break;
            }
        }

        // Check for valid moves in the left direction

        for (int i = currentCol - 1; i >= 0; i--) {
            if (board.check(currentRow, i, isWhite,GetType())) {
                validMoves.push_back(Position(currentRow, i));
            } else {
                break;
            }
        }

        return validMoves;
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
        std::vector<Position> validMoves;

        int currentRow = pos.getRow();
        int currentCol = pos.getCol();
        int newRow ;
        int newCol ;

        // Check for valid moves in the forward direction
        newCol = currentCol + 1;
        newRow = currentRow + 2;

        if(newRow>=0 && newRow<8 && newCol>=0 && newCol<8){
            if (board.check(newRow, newCol, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(newRow, newCol));
            }
        }
        newCol = currentCol - 1;
        newRow = currentRow + 2;
        if(newRow>=0 && newRow<8 && newCol>=0 && newCol<8){
            if (board.check(newRow, newCol, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(newRow, newCol));
            }
        }
        // Check for valid moves in the backward direction
        newCol = currentCol + 1;
        newRow = currentRow - 2;
        if(newRow>=0 && newRow<8 && newCol>=0 && newCol<8){
            if (board.check(newRow, newCol, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(newRow, newCol));
            }
        }
        newCol = currentCol - 1;
        newRow = currentRow - 2;
        if(newRow>=0 && newRow<8 && newCol>=0 && newCol<8){
            if (board.check(newRow, newCol, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(newRow, newCol));
            }
        }
        

        // Check for valid moves in the right direction
        newCol = currentCol + 2;
        newRow = currentRow + 1;
        if(newRow>=0 && newRow<8 && newCol>=0 && newCol<8){
            if (board.check(newRow, newCol, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(newRow, newCol));
            }
        }
        

        newCol = currentCol + 2;
        newRow = currentRow - 1;
        if(newRow>=0 && newRow<8 && newCol>=0 && newCol<8){
            if (board.check(newRow, newCol, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(newRow, newCol));
            }
        }
        

        // Check for valid moves in the left direction

        newCol = currentCol - 2;
        newRow = currentRow + 1;
        if(newRow>=0 && newRow<8 && newCol>=0 && newCol<8){
            if (board.check(newRow, newCol, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(newRow, newCol));
            }
        }
        
        newCol = currentCol - 2;
        newRow = currentRow - 1;
        if(newRow>=0 && newRow<8 && newCol>=0 && newCol<8){
            if (board.check(newRow, newCol, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(newRow, newCol));
            }
        }
        

        return validMoves;
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
        std::vector<Position> validMoves;
        int currentRow = pos.getRow();
        int currentCol = pos.getCol();

        // Check for valid moves in the forward right direction
        for (int i = 1; currentRow + i < 8 && currentCol + i < 8; i++) {
            if (board.check(currentRow + i, currentCol + i, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(currentRow + i, currentCol + i));
            } else {
                break;
            }
        }

        // Check for valid moves in the forward left direction

        for (int i = 1; currentRow + i < 8 && currentCol - i >= 0; i++) {
            if (board.check(currentRow + i, currentCol - i, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(currentRow + i, currentCol - i));
            } else {
                break;
            }
        }

        // Check for valid moves in the backward right direction

        for (int i = 1; currentRow - i >= 0 && currentCol + i < 8; i++) {
            if (board.check(currentRow - i, currentCol + i, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(currentRow - i, currentCol + i));
            } else {
                break;
            }
        }

        // Check for valid moves in the backward left direction

        for (int i = 1; currentRow - i >= 0 && currentCol - i >= 0; i++) {
            if (board.check(currentRow - i, currentCol - i, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(currentRow - i, currentCol - i));
            } else {
                break;
            }
        }

        return validMoves;
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
        std::vector<Position> validMoves;
        int currentRow = pos.getRow();
        int currentCol = pos.getCol();

        // Check for valid moves in the forward direction
        for (int i = currentRow + 1; i < 8; i++) {
            if (board.check(i, currentCol, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(i, currentCol));
            } 
        }

        // Check for valid moves in the backward direction

        for (int i = currentRow - 1; i >= 0; i--) {
            if (board.check(i, currentCol, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(i, currentCol));
            } 
        }

        // Check for valid moves in the right direction

        for (int i = currentCol + 1; i < 8; i++) {
            if (board.check(currentRow, i, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(currentRow, i));
            } 
        }

        // Check for valid moves in the left direction

        for (int i = currentCol - 1; i >= 0; i--) {
            if (board.check(currentRow, i, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(currentRow, i));
            } 
        }

        // Check for valid moves in the forward right direction

        for (int i = 1; currentRow + i < 8 && currentCol + i < 8; i++) {
            if (board.check(currentRow + i, currentCol + i, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(currentRow + i, currentCol + i));
            } 
        }

        // Check for valid moves in the forward left direction

        for (int i = 1; currentRow + i < 8 && currentCol - i >= 0; i++) {
            if (board.check(currentRow + i, currentCol - i, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(currentRow + i, currentCol - i));
            }
        }

        // Check for valid moves in the backward right direction

        for (int i = 1; currentRow - i >= 0 && currentCol + i < 8; i++) {
            if (board.check(currentRow - i, currentCol + i, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(currentRow - i, currentCol + i));
            } 
        }

        // Check for valid moves in the backward left direction

        for (int i = 1; currentRow - i >= 0 && currentCol - i >= 0; i++) {
            if (board.check(currentRow - i, currentCol - i, isWhite,GetType(),currentRow,currentCol)) {
                validMoves.push_back(Position(currentRow - i, currentCol - i));
            } 
        }

        return validMoves;
    }
    /*
    Methods For King Class
    */
    King::King(int r, int c, bool isWhite) : Piece(r, c, isWhite,PieceType::KING), isCheck(false),CheckingPiece(0, 0) {}
    bool King::move(int r, int c,ChessBoard & board) {
        /*
        King's Movement Logic
        */
        int currentRow=pos.getRow();
        int currentCol=pos.getCol();

        if(abs(currentRow-r)<=1 && abs(currentCol-c)<=1){
            if(board.check(r,c, isWhite,GetType(),currentRow,currentCol)){
                pos.changePosition(r,c);
                return true;
            }
        }
        return false;
    }
    void King::display() const{
        std::cout << (isWhite ? "K" : "k");
    }
    bool King::isCheckMate(ChessBoard&board){
        if(isCheck){
            std::vector<Position> validMoves = getValidMoves(board);
            if(validMoves.size()==0){
                return true;
            }
        }
        return false;
    }
    bool King::isChecked(){
        return isCheck;
    }
    void King::CheckKing(Position p){
        isCheck=true;
        CheckingPiece=p;
    }
    std::vector<Position> King::getValidMoves(ChessBoard&board){
        std::vector<Position> validMoves;
        int currentRow = pos.getRow();
        int currentCol = pos.getCol();

        // Check for valid moves in the forward direction
        
        if (board.check(currentRow + 1, currentCol, isWhite,GetType(),currentRow,currentCol)) {
            validMoves.push_back(Position(currentRow + 1, currentCol));
        }
        if (board.check(currentRow + 1, currentCol + 1, isWhite,GetType(),currentRow,currentCol)) {
            validMoves.push_back(Position(currentRow + 1, currentCol + 1));
        }
        if (board.check(currentRow + 1, currentCol - 1, isWhite,GetType(),currentRow,currentCol)) {
            validMoves.push_back(Position(currentRow + 1, currentCol - 1));
        }

        // Check for valid moves in the backward direction

        if (board.check(currentRow - 1, currentCol, isWhite,GetType(),currentRow,currentCol)) {
            validMoves.push_back(Position(currentRow - 1, currentCol));
        }
        if (board.check(currentRow - 1, currentCol + 1, isWhite,GetType(),currentRow,currentCol)) {
            validMoves.push_back(Position(currentRow - 1, currentCol + 1));
        }
        if (board.check(currentRow - 1, currentCol - 1, isWhite,GetType(),currentRow,currentCol)) {
            validMoves.push_back(Position(currentRow - 1, currentCol - 1));
        }
        
        // Check for valid moves in the right direction

        if (board.check(currentRow, currentCol + 1, isWhite,GetType(),currentRow,currentCol)) {
            validMoves.push_back(Position(currentRow, currentCol + 1));
        }

        // Check for valid moves in the left direction

        if (board.check(currentRow, currentCol - 1, isWhite,GetType(),currentRow,currentCol)) {
            validMoves.push_back(Position(currentRow, currentCol - 1));
        }

        return validMoves;

        

    }   