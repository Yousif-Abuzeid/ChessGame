#include "../lib/App.hpp" // Include the header file for the App class to access its functionalities
#include <iostream>       // Include the iostream library for input and output operations
#include <vector>        // Include the vector library for using dynamic arrays

/*
Main loop function for managing the chess game.
This function initializes the game board and controls the flow of the game.
*/
void mainLoop() {
    ChessBoard board;  // Create an instance of the ChessBoard class
    std::system("clear"); // Clear the terminal screen for a clean display
    board.display();   // Display the initial state of the chessboard
    int counter = 0;   // Counter to track the number of turns taken
    bool isWhite = true; // Boolean to indicate if it is White's turn

    // Main game loop
    std::string userInput; // Variable to hold user input for moves
    do {
        WhosTurn(counter, isWhite); // Call the function to display whose turn it is
        std::vector<int> userMove = getMove(userInput); // Get the user's move input
        
        // Exit the game if the user types "exit"
        if (userInput == "exit") {
            break; // Break out of the loop to end the game
        }

        std::system("clear"); // Clear the screen again for the next display
        // Attempt to move the piece on the board
        board.move(userMove[0], userMove[1], userMove[2], userMove[3], isWhite);
        board.display(); // Display the updated state of the chessboard

    } while (true); // Loop indefinitely until the user decides to exit
}

/*
Function to determine whose turn it is.
This function updates the counter and sets the boolean to indicate the current player.
Parameters:
    - counter: Reference to an integer that keeps track of the number of turns taken.
    - isWhite: Boolean reference to indicate if it's White's turn or not.
*/
void WhosTurn(int &counter, bool isWhite) {
    if (counter % 2 == 0) { // Check if the counter is even
        counter++; // Increment the counter for the next turn
        std::cout << "White's Move" << std::endl; // Notify that it's White's turn
        isWhite = true; // Set isWhite to true
    } else { // If the counter is odd
        counter++; // Increment the counter for the next turn
        std::cout << "Black's Move" << std::endl; // Notify that it's Black's turn
        isWhite = false; // Set isWhite to false
    }
}

/*
Function to get the user's move input.
This function prompts the user for their move, converts the input into numeric coordinates,
and returns them as a vector.
Parameters:
    - userMove: Reference to a string where the user's input will be stored.
Returns:
    - A vector of integers representing the starting and ending positions on the chessboard.
*/
std::vector<int> getMove(std::string &userMove) {
    std::cout << "Enter your move: "; // Prompt the user for their move
    std::cin >> userMove; // Read the user input
    // Convert the move from letters to numbers
    int r1 = userMove[1] - '1'; // Convert the starting row from character to integer (0-indexed)
    int c1 = userMove[0] - 'A'; // Convert the starting column from character to integer (0-indexed)
    int r2 = userMove[3] - '1'; // Convert the ending row from character to integer (0-indexed)
    int c2 = userMove[2] - 'A'; // Convert the ending column from character to integer (0-indexed)
    
    // Return a vector containing the starting and ending positions
    return {r1, c1, r2, c2};
}
