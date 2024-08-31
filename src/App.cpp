#include "../lib/App.hpp"
#include <iostream>
void mainLoop(){
        ChessBoard board;
    std::system("clear");
    board.display();
    int counter =0;
    bool isWhite = true;
    // Play the game
    std::string move;
    do{
        if(counter%2 == 0){
            counter++;
            std::cout << "White's Move" << std::endl;
            isWhite=true;
        }else{
            counter++;
            std::cout << "Black's Move" << std::endl;
            isWhite=false;
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
        std::system("clear");
        board.move(r1, c1, r2, c2,isWhite);
        board.display();
        
    } while (true);

    

}