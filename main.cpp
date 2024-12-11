#include "NumericalTicTacToe.h"

int main() {
    // Create the game board
    NumericalTicTacToeBoard board;

    // Create two players
    NumericalTicTacToePlayer player1("Player 1", 1, true); // Odd numbers
    RandomNumericalTicTacToePlayer player2("Player 2", 2, false); // Even numbers

    // Assign the board to players
    player1.setBoard(&board);
    player2.setBoard(&board);

    // Set up the players array
    Player<int>* players[2] = { &player1, &player2 };

    // Create the game manager and run the game
    GameManager<int> game(&board, players);
    game.run();

    return 0;
}
