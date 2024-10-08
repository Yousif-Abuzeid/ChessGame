#include "../lib/ChessBoard.hpp"

#include <iostream>
#include <ostream>

/*
Constructor For the Board
*/
ChessBoard::ChessBoard(){
    board.resize(8, std::vector<Piece*>(8, nullptr));
        for (int i = 0; i < 8; i++) {
            board[1][i] = new Pawn(1, i, true);
            board[6][i] = new Pawn(6, i, false);
        }
        board[0][0] = new Rook(0, 0, true); 
        board[0][7] = new Rook(0, 7, true); // White Rooks
        board[7][0] = new Rook(7, 0, false); 
        board[7][7] = new Rook(7, 7, false); // Black Rooks
        board[0][1] = new Knight(0, 1, true);
        board[0][6] = new Knight(0, 6, true); // White Knights
        board[7][1] = new Knight(7, 1, false); 
        board[7][6] = new Knight(7, 6, false); // Black Knights
        board[0][2] = new Bishop(0, 2, true);
        board[0][5] = new Bishop(0, 5, true); // White Bishops
        board[7][2] = new Bishop(7, 2, false); 
        board[7][5] = new Bishop(7, 5, false); // Black Bishops
        board[0][3] = new Queen(0, 3, true); // White Queen
        board[7][3] = new Queen(7, 3, false); // Black Queen
        board[0][4] = new King(0, 4, true); // White King
        board[7][4] = new King(7, 4, false); // Black King
}

/*
Destructor for the Board
*/
ChessBoard::~ChessBoard(){
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete board[i][j];
        }
    }
}
/*
Method to display the board
*/
void ChessBoard::display() const {
    std::cout << "  A B C D E F G H" << std::endl;
    for(int i = 0; i < 8; i++){
        std::cout << i + 1 << " ";
        for(int j = 0; j < 8; j++){
            if(board[i][j] != nullptr){
                board[i][j]->display();
            }else{
                std::cout << "-";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

/*
Method to move the pieces
*/
std::ostream& operator<<(std::ostream& os,const std::vector<Position> &pos){
    for(int i = 0; i < pos.size(); i++){
        os<<pos[i].getRow()<<" "<<pos[i].getCol()<<std::endl;
    }
    return os;
}

bool ChessBoard::move(int r1, int c1, int r2, int c2,bool isWhite){
    if(board[r1][c1] ->isWhitePiece() != isWhite){
        if(isWhite){
                std::cout<<"It is not your turn it's White's"<<std::endl;

        }else{
                std::cout<<"It is not your turn it's Black's"<<std::endl;

        }
        return false;
    }
    if(r1 < 0 || r1 > 7 || c1 < 0 || c1 > 7 || r2 < 0 || r2 > 7 || c2 < 0 || c2 > 7){
        return false;
    }
    if(board[r1][c1] == nullptr){
       
                return false;

    }
    
    if(board[r2][c2]!=nullptr &&board[r2][c2]->GetType()==PieceType::KING){
        std::cout<<"YOU CANNOT KILL THE KING"<<std::endl;
        return false;
    }

    
    // Use the move method from the piece class
    if(board[r1][c1]->move(r2, c2, *this)){
        
        board[r2][c2] = std::move(board[r1][c1]);
        board[r1][c1] = nullptr;
        int newRow=0;
        int newCol=0;
        std::vector<Position> validMoves = board[r2][c2]->getValidMoves(*this);
        for(int i = 0; i < validMoves.size(); i++){
            newRow = validMoves[i].getRow();
            newCol = validMoves[i].getCol();
            //std::cout<<newRow<<" "<<newCol<<std::endl;
            if(board[newRow][newCol] != nullptr && board[newRow][newCol]->GetType() == PieceType::KING){
                //std::cout<<"Check"<<std::endl;
                King* king = dynamic_cast<King*>(board[newRow][newCol]);
                if (king != nullptr) {
                    // Do something with the king object
                    king->CheckKing(Position(r2,c2));
                }
                if(king->isChecked()){
                    if(CanBeKilled(r2, c2, board[r2][c2]->isWhitePiece())){
                        std::cout<<"Check"<<std::endl;
                    }else{
                    if(king->isCheckMate(*this)){
                        std::cout<<"CheckMate"<<std::endl;
                        exit(0);
                    }
                    }
                }
            }
        }

        return true;
    }
    std::cout<<"Invalid Move"<<std::endl;
    return false;
}

/*
Function to Kill Pieces
*/
void ChessBoard::killPiece(int r, int c){
    /*delete ChessBoard::board[r][c];
    ChessBoard::board[r][c] = nullptr;*/
}
/*
Check Pawn Move Valid
*/
bool CheckPawnMoveValid(int r,int c,ChessBoard& Board,bool isWhite,bool forAkilling=false){
    if(forAkilling){
        
        if (Board.board[r][c] != nullptr && Board.board[r][c]->isWhitePiece() != isWhite){
            return true;
        }
    }else{
    if(Board.board[r][c] == nullptr){
        return true;
    }

    if(Board.board[r][c] != nullptr && Board.board[r][c]->isWhitePiece() == isWhite){
        return false;
    }
    
    
    return false;
}
    return false;

}
/*
Check Rook Move Valid
*/
bool CheckRookMoveValid(int r1,int c1,int r2,int c2, ChessBoard& Board,bool iswhite){
    if(r1 == r2){
        for(int i = c1 + 1; i < c2; i++){
            if(Board.board[r1][i] != nullptr){
                return false;
            }
        }
        if(Board.board[r2][c2] != nullptr && Board.board[r2][c2]->isWhitePiece() == iswhite){
            return false;
        }
        return true;
    }
    if(c1 == c2){
        for(int i = r1 + 1; i < r2; i++){
            if(Board.board[i][c1] != nullptr){
                return false;
            }
        }
        if(Board.board[r2][c2] != nullptr && Board.board[r2][c2]->isWhitePiece() == iswhite){
            return false;
        }
        return true;
    }
    return false;
}
/*
Check Bishop Move Valid
*/
bool CheckBoolMoveValid(int r1,int c1,int r2,int c2, ChessBoard& Board,bool iswhite){
    if(abs(r1 - r2) == abs(c1 - c2)){
        int row = r1 < r2 ? r1 + 1 : r1 - 1;
        int col = c1 < c2 ? c1 + 1 : c1 - 1;
        while(row != r2 && col != c2){
            if(Board.board[row][col] != nullptr){
                return false;
            }
            row = r1 < r2 ? row + 1 : row - 1;
            col = c1 < c2 ? col + 1 : col - 1;
        }
        if(Board.board[r2][c2] != nullptr && Board.board[r2][c2]->isWhitePiece() == iswhite){
            return false;
        }
        return true;
    }
    return false;
}
/*
Check Knight Move Valid
*/
bool CheckKnightMoveValid(int r1,int c1,int r2,int c2, ChessBoard& Board,bool iswhite){
    if((abs(r1 - r2) == 2 && abs(c1 - c2) == 1) || (abs(r1 - r2) == 1 && abs(c1 - c2) == 2)){
        if(Board.board[r2][c2] != nullptr && Board.board[r2][c2]->isWhitePiece() == iswhite){
            return false;
        }
        return true;
    }
    return false;
}
/*
Check Queen Move Valid
*/
bool CheckQueenMoveValid(int r1,int c1,int r2,int c2, ChessBoard& Board,bool iswhite){
    if(CheckBoolMoveValid(r1, c1, r2, c2, Board, iswhite) || CheckRookMoveValid(r1, c1, r2, c2, Board, iswhite)){
        return true;
    }
    return false;
}

/*
check function
*/
bool ChessBoard::check(int r2,int c2, bool isWhite,PieceType type,int r1, int c1,bool forAkilling){
   switch (type) {
   case PieceType::PAWN:
    if(CheckPawnMoveValid(r2, c2, *this, isWhite,forAkilling)){
        return true;
    }
   break;
   case PieceType::ROOK:
   if(CheckRookMoveValid(r1, c1,r2,c2,*this,isWhite)){
       return true;
   }
   case PieceType::BISHOP:
   if(CheckBoolMoveValid(r1, c1,r2,c2,*this,isWhite)){
       return true;
   }
   case PieceType::KNIGHT:
    if(CheckKnightMoveValid(r1, c1,r2,c2,*this,isWhite)){
         return true;
    }
   case PieceType::QUEEN:
    if(CheckQueenMoveValid(r1, c1,r2,c2,*this,isWhite)){
        return true;
    }
   case PieceType::KING:
    default:
        break;
   }
   return false;
}

/*  
Check if the
*/


bool ChessBoard::CanBeKilled(int r, int c,bool isWhite){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j] != nullptr && board[i][j]->isWhitePiece() != isWhite){
                std::vector<Position> validMoves = board[i][j]->getValidMoves(*this);
                for(int k = 0; k < validMoves.size(); k++){
                    if(validMoves[k].getRow() == r && validMoves[k].getCol() == c){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

