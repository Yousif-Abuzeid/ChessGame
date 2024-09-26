#include "../lib/basePiece.hpp"


    /*
    * ------------------------------------------------------------------------------------------------
    *   Position Class
    * ------------------------------------------------------------------------------------------------
    *
    *
    */

    /*
        Constructor for position
    */
    Position::Position(int r , int c) : row(r), col(c) {}
    /*
        Get Row Method
        Returns the current row of the piece
    */
    int Position:: getRow() const { return row; }
    /*
        Get Column Method
        Returns the current Column of the piece
    */
    int Position::getCol() const { return col; }
    /*
        is Equals Methods
        Check the if input postion is equal to the piece position
    */
    bool Position:: isEquals(const Position& p) const {
        return row == p.getRow() && col == p.getCol();;
    }
    /*
        Change Postion Method 
        Change the position of the piece
     */
    void Position::changePosition(int r, int c){
        row = r;
        col = c;
    } ;


    /*
    * ------------------------------------------------------------------------------------------------
    *   Piece Class
    * ------------------------------------------------------------------------------------------------
    *
    *
    */
    
    /*
        Constructor
    */
    Piece::Piece(int r, int c, bool isWhite ,PieceType type) : pos(r, c), isWhite(isWhite),type(type) {}

   /*
    *
    * Name:   isWhitePiece Method
    * Description:  Method to check the color of the piece
    * Input: None
    * Output: true if piece is white
    *         false if piece is black
    *
    *
   */
    bool Piece::isWhitePiece() const {
        return isWhite;
    }
    /*
    *
    * Name:   GetType Method
    * Description:  Method to get the type of the piece
    * Input: None
    * Output: PAWN,ROOK,BISHOP,KNIGHT,QUEEN,KING
    *
    *
   */
    PieceType Piece::GetType() const{
        return type;
    }