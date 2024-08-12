#include "ChessBoard.hpp"
#include <string>
#include <iostream>

int main(){
    ChessBoard board;
    board.display();
    int counter =0;
    // Play the game
    std::string move;
    do{
        if(counter%2 == 0){
            counter++;
            std::cout << "White's Move" << std::endl;
        }else{
            counter++;
            std::cout << "Black's Move" << std::endl;
        }
        std::cout << "Enter your move: ";
        std::cin >> move;
        if(move == "exit"){
            break;
        }
        // Convert the move from letters to numbers
        int r1 = move[1] - '1';
        int c1 = move[0] - 'A';
        int r2 = move[3] - '1';
        int c2 = move[2] - 'A';
        board.move(r1, c1, r2, c2);
        board.display();
        
    } while (true);

    
    return 0;
}